#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"
#include <iostream>

class Webserver{
    private:
        Request currentRequest;
        bool busy;
    
    public: 

    void assignRequest(const Request& request);
    void runCycle();

    bool isBusy() const;
};

#endif