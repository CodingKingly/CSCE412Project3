/**
 * @file Webserver.h
 * @brief Declares a web server that processes one request at a time.
 * @author Abel Asteway
 * @date 2026
 */


#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"
#include <iostream>

/**
 * @class Webserver
 * @brief Represents one server managed by a load balancer.
 *
 * A Webserver accepts one request, processes it for the required number
 * of clock cycles, and becomes available after the request is completed.
 */
class Webserver{
    private:
        Request currentRequest;/**< Request currently being processed. */
        

    public: 
    bool busy = false;/**< Indicates whether the server has an active request. */
    int ServerID; /**< Unique identification number for the server. */

    /**
     * @brief Assigns a request to the server.
     * @param request The request that the server will process.
     */
    void assignRequest(const Request& request);


    /**
     * @brief Returns the request currently assigned to the server.
     * @return The server's current Request object.
     */
    Request seeRequest();

    /**
     * @brief Processes the current request for one clock cycle.
     *
     * The request's remaining processing time is reduced by one. The
     * server becomes idle when the time reaches zero.
     */
    void runCycle();

    /**
     * @brief Determines whether the server is processing a request.
     * @return true if the server is busy; otherwise false.
     */
    bool isBusy() const;
};

#endif