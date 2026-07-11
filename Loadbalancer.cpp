#include "Loadbalancer.h"

void Loadbalancer::loadBalancerStartCycle(int startCycle){
    clockCycle = startCycle;
}

void Loadbalancer::loadBalancerStartServers(int startServers){
    numServers = startServers;
    for(int i = 0; i < startServers; i++){
        Webserver newWbeserver;
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
                numServers++;
                cout << "added a new server: " << endl;
            }
        }

        //Assign the servers
        for(int i = 0; i < numServers; i++){
            if(!WebserverVec.at(i).isBusy() && !requestQueue.empty()){
                WebserverVec.at(i).assignRequest(requestQueue.front());
                requestQueue.pop();
            }
        }

        //


    }
} 