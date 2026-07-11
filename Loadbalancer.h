#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <queue>
#include "Request.h"
#include "Webserver.h"

class Loadbalancer{
    private: 
        std::queue<Request> requestQueue; 
        std::vector<Webserver> WebserverVec; 
        int clockCycle = 0;
        // int numServers = 0;

    public:
        int nextServerID;

        void loadBalancerStartCycle(int startCycle);
        void loadBalancerStartServers(int startServers);
        void loadBalancerStartRequest();

        void loadbalancerStart();

        

};


#endif