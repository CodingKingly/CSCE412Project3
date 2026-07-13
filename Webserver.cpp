/**
 * @file Webserver.cpp
 * @brief Implements request assignment and clock-cycle processing.
 * @author Abel Asteway
 * @date 2026
 */
#include "Webserver.h"

void Webserver::runCycle()
{
    if (!busy)
    {
        return;
    }

    currentRequest.totalTime = currentRequest.totalTime - 1;
    if (currentRequest.totalTime <= 0)
    {
        cout << "DONE with Request " << currentRequest.IPin << endl;
        busy = false;
    }
}

void Webserver::assignRequest(const Request &request)
{
    busy = true;
    currentRequest = request;
    std::cout << "Assigned new Request " << request.IPin << endl;;
}

bool Webserver::isBusy() const
{
    return busy;
}

Request Webserver::seeRequest(){
    return currentRequest;
}
