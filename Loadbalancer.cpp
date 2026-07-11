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

        cout << "Clock Cycle: " << currentClockCycle << " has started";

        //Helps current assign Servers to a task 
        for(int i = 0; i < numServers; i++){
            if(!WebserverVec.at(i).isBusy() && !requestQueue.empty()){
                WebserverVec.at(i).assignRequest(requestQueue.front());
                requestQueue.pop();
            }
        }
        
    }
} 