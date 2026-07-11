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
        cout << "DONE with Request " << currentRequest.IPin;
        busy = false;
    }
}

void Webserver::assignRequest(const Request &request)
{
    busy = true;
    currentRequest = request;
    std::cout << "Assigned new Request " << request.IPin;
}

bool Webserver::isBusy() const
{
    return busy;
}
