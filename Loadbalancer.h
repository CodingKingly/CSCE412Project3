#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <queue>
#include "Request.h"
#include "Webserver.h"

class Loadbalancer{
    private: 
        std::queue<Request> requestQueue; 
        std::queue<Webserver> WebserverQueue; 
        int clockCycle = 0;
        int numServers = 0;

    public:
        
        void loadBalancerStartCycle(int startCycle){};
        void loadBalancerStartServers(int startServers){};
        void loadBalancerStartRequest(int startRequest){};

        void createServer();
        void deleteServer();
        void assignServer();

        void loadbalancerStart();

        

};


#endif