/**
 * @file Loadbalancer.cpp
 * @brief Implements queue management, server scaling, and request processing.
 * @author Abel Asteway
 * @date 2026
 */
#include "Loadbalancer.h"

void Loadbalancer::loadBalancerStartCycle(int startCycle){
    clockCycle = startCycle;
}

void Loadbalancer::loadBalancerType(char type){
    jobType = type;
}

void Loadbalancer::addRequest(Request re){
    requestQueue.push(re);
}

bool Loadbalancer::requestQueueempty(){
    return requestQueue.empty();
}

int Loadbalancer::getRequestQueueSize(){
    return requestQueue.size();
}

int Loadbalancer::getServerCount(){
    return WebserverVec.size();
}

int Loadbalancer::getBusyServerCount(){
    int busyServerCount = 0;

    for (const Webserver& server : WebserverVec) {
        if (server.isBusy()) {
            busyServerCount++;
        }
    }

    return busyServerCount;
}

void Loadbalancer::loadBalancerStartServers(int startServers){
    nextServerID = 0;
    for(int i = 0; i < startServers; i++){
        Webserver newWbeserver;
        newWbeserver.ServerID = nextServerID;
        nextServerID++;
        WebserverVec.push_back(newWbeserver);
    }
}

// void Loadbalancer::loadBalancerStartRequest(){
    
//     for(int i = 0; i < WebserverVec.size() * 100 ; i++){
//         Request newrequest = makearandomRequest();
//         requestQueue.push(newrequest);
//     }
// }


void Loadbalancer::OneCylce(){


        //Helps add or delete servers every 50 cycles 
        if (clockCycle % 50 == 0)
        {   //Helps add a server
            if(requestQueue.size() > WebserverVec.size() * 100){
                int numNewServers = (((requestQueue.size() - (WebserverVec.size() * 100)) + 99) / 100);

                for(int j = 0; j < numNewServers ; j++){
                    Webserver newWbeserver;
                    newWbeserver.ServerID = nextServerID;
                    nextServerID++;
                    WebserverVec.push_back(newWbeserver);
                    
                    cout << "added a new server: " << newWbeserver.ServerID << endl;
                    totalServersAdded++;
                }
            }
            //Helps delete a server
            else if(requestQueue.size() < WebserverVec.size() * 50){
                
                    int numDelServers =  ((WebserverVec.size() * 50 - requestQueue.size()) + 49)/50; 
                    for(int j = static_cast<int>(WebserverVec.size()) - 1; j >= 0 && numDelServers > 0 && WebserverVec.size() > 1  ; j--){
                        if(WebserverVec.at(j).isBusy()){
                            continue;
                        }
                        cout << "Deleted a server: " << WebserverVec.at(j).ServerID << endl;
                        WebserverVec.erase(WebserverVec.begin() + j);
                        numDelServers--;
                        totalServersDeleted++;
                    }
            }
        }

        //Assign the servers or Run the server
        for(int i = 0; i < WebserverVec.size(); i++){
            if(!WebserverVec.at(i).isBusy() && !requestQueue.empty()){
                WebserverVec.at(i).assignRequest(requestQueue.front());
                requestQueue.pop();
            }
            else if(WebserverVec.at(i).isBusy()){
                WebserverVec.at(i).runCycle();

                if(WebserverVec.at(i).seeRequest().totalTime != 0){
                    cout << "Server " << WebserverVec.at(i).ServerID << 
                    " completed one clock cycle of IP" << WebserverVec.at(i).seeRequest().IPin << 
                    " time left of request is: " << WebserverVec.at(i).seeRequest().totalTime << endl;
                }
                else{
                    cout << "Server " << WebserverVec.at(i).ServerID << 
                    " just completed it's task with the IPin " << WebserverVec.at(i).seeRequest().IPin << endl;
                }
            }
            
        }

        //add to the current clock cycle 
        clockCycle++;
} 