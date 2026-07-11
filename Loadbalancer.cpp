#include "Loadbalancer.h"

void Loadbalancer::loadBalancerStartCycle(int startCycle){
    clockCycle = startCycle;
}

void Loadbalancer::loadBalancerStartServers(int startServers){
    numServers = startServers;
    for(int i = 0; i < startServers; i++){
        Webserver newWbeserver;
        newWbeserver.ServerID = i;
        WebserverVec.push_back(newWbeserver);
    }
}

void Loadbalancer::loadBalancerStartRequest(){
    
    for(int i = 0; i < numServers * 100 ; i++){
        Request newrequest = makearandomRequest();
        requestQueue.push(newrequest);
    }
}

void Loadbalancer::loadbalancerStart(){

    int currentClockCycle = 0;

    while(currentClockCycle <= clockCycle){

        cout << "Clock Cycle: " << currentClockCycle << " has started" << endl;

        //Helps current assign Servers to a task 
        if(requestQueue.size() < numServers * 100){
            int numNewServers = ceil((requestQueue.size() - (numServers * 100))/100);
            for(int j = 0; j < numNewServers ; j++){
                Webserver newWbeserver;
                WebserverVec.push_back(newWbeserver);
                newWbeserver.ServerID = numServers + 1 + j;
                numServers++;
                cout << "added a new server: " << endl;
            }
        }

        //Assign the servers or Run the server
        for(int i = 0; i < numServers; i++){
            if(!WebserverVec.at(i).isBusy() && !requestQueue.empty()){
                WebserverVec.at(i).assignRequest(requestQueue.front());
                WebserverVec.at(i).busy = true;
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
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> addRequest(0, 5);
        
        int randomNumForRequest = addRequest(gen);
        if(randomNumForRequest == 0){
            Request newrequest = makearandomRequest();
            requestQueue.push(newrequest);
        }

        //add to the current clock cycle 
        currentClockCycle++;
    }
} 