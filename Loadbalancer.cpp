#include "Loadbalancer.h"

void Loadbalancer::loadBalancerStartCycle(int startCycle){
    clockCycle = startCycle;
}

void Loadbalancer::loadBalancerStartServers(int startServers){
    numServers = startServers;
    for(int i = 0; i < startServers; i++){
        Webserver newWbeserver;
        WebserverQueue.push(newWbeserver);
    }
}

void Loadbalancer::loadBalancerStartRequest(int startServers){
    numServers = startServers;
    for(int i = 0; i < startServers; i++){
        Request newrequest;
        requestQueue.push(newrequest);
    }
}



void Loadbalancer::loadBalancerStartServers(int)
void Loadbalancer::loadbalancerStart(){
    Request newRequest = makearandomRequest();
    while(!requestQueue.empty()){
        cout << "The " << clockCycle << " has started";
        if()
    }
} 