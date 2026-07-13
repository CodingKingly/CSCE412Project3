/**
 * @file Loadbalancer.h
 * @brief Declares the Loadbalancer class used to manage requests and servers.
 * @author Abel Asteway
 * @date 2026
 */

#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <queue>
#include <vector>
#include <cstddef>

#include "Request.h"
#include "Webserver.h"

/**
 * @class Loadbalancer
 * @brief Manages a request queue and a dynamic collection of web servers.
 *
 * The load balancer assigns queued requests to idle servers. It also
 * adds servers when the queue becomes excessively large and removes
 * idle servers when the queue becomes too small.
 */
class Loadbalancer{
    private: 
        std::vector<Webserver> WebserverVec; /**< Servers managed by this instance. */
        std::queue<Request> requestQueue; /**< Requests waiting for service. */
        int clockCycle = 0; /**< Current load-balancer clock cycle. */
        // int numServers = 0;

    public:
        int nextServerID;/**< Identification number assigned to the next server. */
        char jobType; /**< Identification of the jobtype. */
        int totalServersAdded = 0; /**< Servers added*/
        int totalServersDeleted = 0;/**< Servers deleted*/

        /**
         * @brief Assigns the type of the workload
         * @param type Defines the type of the workload .
         */
        void loadBalancerType(char type);

        /**
         * @brief Assigns a starting cycle
         * @param startCycle the initial clock cycle.
         */
        void loadBalancerStartCycle(int startCycle); 
        
        /**
         * @brief Gets the amount of busy servers
         * @return the amount of bust servers
         */
        int getBusyServerCount();

        /**
         * @brief Creates the requested number of starting web servers.Currently Unsused
         * @param startServers Number of servers to create.
         */
        void loadBalancerStartServers(int startServers);

        /**
        * @brief Returns the number of requests waiting in the queue.
        * @return Number of queued requests.
        */
        int getRequestQueueSize();

        /**
         * @brief Returns the number of requests waiting in the queue.
         * @return Number of queued requests.
         */
        bool requestQueueempty();

        /**
         * @brief Returns the number of sercers
         * @return Number of servers .
         */
        int getServerCount();

        /**
         * @brief Adds a request to the back of the request queue.
         * @param request Request to add.
         */
        void addRequest(Request re);

         /**
         * @brief Executes one clock cycle of load-balancer activity.
         *
         * Processes busy servers, assigns requests to idle servers, and
         * periodically adds or removes servers based on queue size.
         */
        void OneCylce();

};


#endif