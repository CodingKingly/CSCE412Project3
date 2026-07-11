#include "Loadbalancer.h"

void Loadbalancer::loadBalancerStartCycle(int startCycle){
    clockCycle = startCycle;
}

void Loadbalancer::loadBalancerStartServers(int startServers){
    numServers = startServers;
    nextServerID = 0;
    for(int i = 0; i < numServers; i++){
        Webserver newWbeserver;
        newWbeserver.ServerID = nextServerID;
        nextServerID++;
        WebserverVec.push_back(newWbeserver);
    }
}

void Loadbalancer::loadBalancerStartRequest(){
    
    for(int i = 0; i < WebserverVec.size() * 100 ; i++){
        Request newrequest = makearandomRequest();
        requestQueue.push(newrequest);
    }
}

void Loadbalancer::loadbalancerStart(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> addRequest(0, 5);
    int currentClockCycle = 0;

    while(currentClockCycle < clockCycle){

        cout << "Clock Cycle: " << currentClockCycle << " has started" << endl;

        //Helps add or delete servers every 50 cycles 
        if (currentClockCycle % 50 == 0)
        {   //Helps add a server
            if(requestQueue.size() > WebserverVec.size() * 100){
                int numNewServers = (((requestQueue.size() - (WebserverVec.size() * 100)) + 99) / 100);

                for(int j = 0; j < numNewServers ; j++){
                    Webserver newWbeserver;
                    newWbeserver.ServerID = nextServerID;
                    nextServerID++;
                    WebserverVec.push_back(newWbeserver);
                    
                    cout << "added a new server: " << newWbeserver.ServerID << endl;
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
                cout << "Server" << WebserverVec.at(i).ServerID << 
                " completed one clock cycle of IP" << WebserverVec.at(i).seeRequest().IPin << 
                " time left of request is: " << WebserverVec.at(i).seeRequest().totalTime << endl;
            }
        }

        //Random chance to add work
        int randomNumForRequest = addRequest(gen);
        if(randomNumForRequest == 0){
            Request newrequest = makearandomRequest();
            requestQueue.push(newrequest);
        }

        //add to the current clock cycle 
        currentClockCycle++;
    }
} 