#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"
#include <iostream>

class Webserver{
    private:
        Request currentRequest;
        

    public: 
    bool busy;
    int ServerID;
    
    void assignRequest(const Request& request);
    Request seeRequest();
    void runCycle();

    bool isBusy() const;
};

#endif