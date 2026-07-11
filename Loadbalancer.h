#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <queue>
#include <vector>
#include <cstddef>
#include "Request.h"
#include "Webserver.h"

class Loadbalancer{
    private: 
        std::vector<Webserver> WebserverVec; 
        std::queue<Request> requestQueue;
        int clockCycle = 0;
        // int numServers = 0;

    public:
        int nextServerID;
        char jobType;
        

        void loadBalancerType(char type);
        void loadBalancerStartCycle(int startCycle);
        void loadBalancerStartServers(int startServers);
        void loadBalancerStartRequest();
        int getRequestQueueSize();
        bool requestQueueempty();
        void addRequest(Request re);

        void OneCylce();

};


#endif