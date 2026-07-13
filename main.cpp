/**
 * @file main.cpp
 * @brief Runs the processing and streaming load-balancer simulation.
 * @author Abel Asteway
 * @date 2026
 */
#include <fstream>
#include <iostream>
#include <random>
#include <iomanip>
#include "Loadbalancer.h"
#include "Request.h"
using namespace std;

 /**
 * @brief Entry point for the load-balancer simulation.
 *
 * Requests the starting server count and simulation duration, creates
 * processing and streaming load balancers, generates the initial queue,
 * and executes both load balancers for the selected number of cycles.
 *
 * @return 0 when the simulation completes successfully, or a nonzero
 * value when the user enters invalid input.
 */

int main(){
    // creating a log
    std::ofstream logFile("loadbalancer_log.txt");

    if (!logFile.is_open())
    {
        std::cerr << "The log file could not be created.\n";
        return 1;
    }

    //Get the inputs
    int numServers = 0;
    cout << "Input the starting amount of Servers ";
    cin >> numServers;

    int totalClockCyles;
    cout << endl << "Input the total amount of clock cycles ";
    cin >> totalClockCyles;

    cout << endl << "Starting the load balancer" << endl << 
    "The Starting clock cycles is: " << totalClockCyles << endl
    << "The total servers are: " << numServers << endl 
    << "The starting amount of requests will be Number of Servers * 100: " << numServers * 100;


    //Set up the Load balancers
    int processingServers = (numServers + 1) / 2;
    int streamingServers = numServers / 2;
    Loadbalancer S_loadBalancer;
    S_loadBalancer.loadBalancerStartServers(streamingServers);


    Loadbalancer P_loadBalancer;
    P_loadBalancer.loadBalancerStartServers( processingServers);

    //for the log
   

    logFile << "CSCE 412 Load Balancer Simulation Log\n";
    logFile << "=====================================\n";
    logFile << "Total starting servers: " << numServers << '\n';
    logFile << "Processing servers: " << processingServers << '\n';
    logFile << "Streaming servers: " << streamingServers << '\n';
    logFile << "Total clock cycles: " << totalClockCyles << '\n';
    logFile << "Initial requests: " << numServers * 100 << "\n\n";

    //making the requests
    for(int i = 0; i < numServers * 100 ; i++){
        Request newrequest = makearandomRequest();
        if(newrequest.jobType == 'p'){
            P_loadBalancer.addRequest(newrequest);
        }
        else if(newrequest.jobType == 's'){
            S_loadBalancer.addRequest(newrequest);
        }
    }

    //getting starting size
    std::size_t startingQueueSize_P = P_loadBalancer.getRequestQueueSize();
    std::size_t startingQueueSize_S = S_loadBalancer.getRequestQueueSize();
    std::size_t startingQueueSize = P_loadBalancer.getRequestQueueSize() + S_loadBalancer.getRequestQueueSize();

    std::size_t startingServerCount = P_loadBalancer.getServerCount() + S_loadBalancer.getServerCount();
    std::size_t startingServerCount_P = P_loadBalancer.getServerCount();
    std::size_t startingServerCount_S = S_loadBalancer.getServerCount();
    
    int currentClockCycle = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> addRequest(0, 5);

    //Starting the loop
    while(currentClockCycle < totalClockCyles ){

        cout << "Clock Cycle: " << currentClockCycle << " has started" << endl
        << "There are this many S_request left " << S_loadBalancer.getRequestQueueSize() << endl <<
        "There are this many P_request left " << P_loadBalancer.getRequestQueueSize() << endl;

        logFile
        << "Cycle " << currentClockCycle
        << " | P Servers: " << P_loadBalancer.getServerCount()
        << " | P Busy: " << P_loadBalancer.getBusyServerCount()
        << " | P Queue: " << P_loadBalancer.getRequestQueueSize()
        << " | S Servers: " << S_loadBalancer.getServerCount()
        << " | S Busy: " << S_loadBalancer.getBusyServerCount()
        << " | S Queue: " << S_loadBalancer.getRequestQueueSize()
        << '\n';

        cout << "-----S Cycle-----" << endl;
        S_loadBalancer.OneCylce();

        cout << "-----P Cycle-----" << endl;
        P_loadBalancer.OneCylce();
        
        //Generate random request 
        int randomNumForRequest = addRequest(gen);
        if(randomNumForRequest == 0){

            Request newrequest = makearandomRequest();
            if(newrequest.jobType == 'p'){
            P_loadBalancer.addRequest(newrequest);
                }
            else if(newrequest.jobType == 's'){
            S_loadBalancer.addRequest(newrequest);
                }  

            logFile
            << "Cycle " << currentClockCycle
            << ": New " << newrequest.jobType
            << " request arrived from "
            << newrequest.IPin
            << " with processing time "
            << newrequest.totalTime
            << '\n';
        }

        currentClockCycle++;
    }


    std::size_t endingQueueSize_P = P_loadBalancer.getRequestQueueSize();
    std::size_t endingQueueSize_S = S_loadBalancer.getRequestQueueSize();
    std::size_t endingQueueSize =  endingQueueSize_P + endingQueueSize_S;
    std::size_t endingServerCount_P = P_loadBalancer.getServerCount();
    std::size_t endingServerCount_S = S_loadBalancer.getServerCount();
    std::size_t endingServerCount = endingServerCount_P + endingServerCount_S;

    int processingServersAdded = P_loadBalancer.totalServersAdded;
    int streamingServersAdded = S_loadBalancer.totalServersAdded;
    int totalServersAdded = processingServersAdded + streamingServersAdded;
    int processingServersDeleted = P_loadBalancer.totalServersDeleted;
    int streamingServersDeleted = S_loadBalancer.totalServersDeleted;
    int totalServersDeleted = processingServersDeleted + streamingServersDeleted;


    // End-status server information
    int activeServers_P = P_loadBalancer.getBusyServerCount();
    int activeServers_S = S_loadBalancer.getBusyServerCount();
    int totalActiveServers = activeServers_P + activeServers_S;
    int inactiveServers_P = static_cast<int>(endingServerCount_P) - activeServers_P;
    int inactiveServers_S =static_cast<int>(endingServerCount_S) - activeServers_S;
    int totalInactiveServers =inactiveServers_P + inactiveServers_S;

    // Each busy server has one request currently being processed.
    int requestsInProgress_P = activeServers_P;
    int requestsInProgress_S = activeServers_S;
    int totalRequestsInProgress = requestsInProgress_P + requestsInProgress_S;

    // Includes queued requests and requests currently being processed.
    std::size_t totalUnfinishedRequests_P =endingQueueSize_P + requestsInProgress_P;

    std::size_t totalUnfinishedRequests_S = endingQueueSize_S + requestsInProgress_S;

    std::size_t totalUnfinishedRequests = totalUnfinishedRequests_P + totalUnfinishedRequests_S;

    double serverUtilization = 0.0;

    if (endingServerCount > 0)
    {
        serverUtilization =
            (static_cast<double>(totalActiveServers) /
            endingServerCount) * 100.0;
    }
    cout << endl << "The load balancer is done running" << endl; 

    logFile << "PROCESSING LOAD BALANCER\n";
    logFile << "Starting queue size: "<< startingQueueSize_P << '\n';
    logFile << "Ending queue size: "<< endingQueueSize_P << '\n';
    logFile << "Starting web servers: "<< startingServerCount_P << '\n';
    logFile << "Ending web servers: "<< endingServerCount_P << '\n';
    logFile << "Web servers added: "<< processingServersAdded << '\n';
    logFile << "Web servers deleted: "<< processingServersDeleted << "\n\n";

    logFile << "STREAMING LOAD BALANCER\n";
    logFile << "Starting queue size: "<< startingQueueSize_S << '\n';
    logFile << "Ending queue size: "<< endingQueueSize_S << '\n';
    logFile << "Starting web servers: "<< startingServerCount_S << '\n';
    logFile << "Ending web servers: "<< endingServerCount_S << '\n';
    logFile << "Web servers added: "<< streamingServersAdded << '\n';
    logFile << "Web servers deleted: "<< streamingServersDeleted << "\n\n";

    logFile << "COMBINED TOTALS\n";
    logFile << "Starting queue size: "<< startingQueueSize << '\n';
    logFile << "Ending queue size: "<< endingQueueSize << '\n';
    logFile << "Starting web servers: "<< startingServerCount << '\n';
    logFile << "Ending web servers: "<< endingServerCount << '\n';
    logFile << "Total web servers added: " << totalServersAdded << '\n';
    logFile << "Total web servers deleted: "<< totalServersDeleted << '\n';

    logFile << "\nEND STATUS\n";
    logFile << "================================\n";

    logFile << "PROCESSING STATUS\n";
    logFile << "Requests remaining in queue: "  << endingQueueSize_P << '\n';
    logFile << "Requests currently processing: "    << requestsInProgress_P << '\n';
    logFile << "Total unfinished requests: "  << totalUnfinishedRequests_P << '\n';
    logFile << "Active/busy servers: "   << activeServers_P << '\n';
    logFile << "Inactive/idle servers: "  << inactiveServers_P << "\n\n";

    logFile << "STREAMING STATUS\n";
    logFile << "Requests remaining in queue: " << endingQueueSize_S << '\n';
    logFile << "Requests currently processing: "  << requestsInProgress_S << '\n';
    logFile << "Total unfinished requests: " << totalUnfinishedRequests_S << '\n';
    logFile << "Active/busy servers: " << activeServers_S << '\n';
    logFile << "Inactive/idle servers: "<< inactiveServers_S << "\n\n";

    logFile << "COMBINED END STATUS\n";
    logFile << "Total requests remaining in queues: "<< endingQueueSize << '\n';
    logFile << "Total requests currently processing: "<< totalRequestsInProgress << '\n';
    logFile << "Total unfinished requests: "<< totalUnfinishedRequests << '\n';
    logFile << "Total active/busy servers: "<< totalActiveServers << '\n';
    logFile << "Total inactive/idle servers: "<< totalInactiveServers << '\n';
    logFile << fixed << setprecision(2);
    logFile << "Server utilization: "<< serverUtilization << "%\n";

    logFile.close();

    cout << "\nLOAD BALANCER SIMULATION SUMMARY\n";
    cout << "================================\n";
    cout << "Clock cycles completed: "<< totalClockCyles << "\n\n";
    cout << "PROCESSING LOAD BALANCER\n";
    cout << "Starting queue size: "<< startingQueueSize_P << '\n';
    cout << "Ending queue size: "<< endingQueueSize_P << '\n';
    cout << "Starting web servers: "<< startingServerCount_P << '\n';
    cout << "Ending web servers: "<< endingServerCount_P << '\n';
    cout << "Web servers added: "<< processingServersAdded << '\n';
    cout << "Web servers deleted: "<< processingServersDeleted << "\n\n";
    cout << "STREAMING LOAD BALANCER\n";
    cout << "Starting queue size: "<< startingQueueSize_S << '\n';
    cout << "Ending queue size: "<< endingQueueSize_S << '\n';
    cout << "Starting web servers: "<< startingServerCount_S << '\n';
    cout << "Ending web servers: "<< endingServerCount_S << '\n';
    cout << "Web servers added: "<< streamingServersAdded << '\n';
    cout << "Web servers deleted: "<< streamingServersDeleted << "\n\n";
    cout << "COMBINED TOTALS\n";
    cout << "Starting queue size: "<< startingQueueSize << '\n';
    cout << "Ending queue size: "<< endingQueueSize << '\n';
    cout << "Starting web servers: " << startingServerCount << '\n';
    cout << "Ending web servers: " << endingServerCount << '\n';

    cout << "Total web servers added: " << totalServersAdded << '\n';

    cout << "Total web servers deleted: " << totalServersDeleted << '\n';

    cout << "\nEND STATUS\n";
    cout << "================================\n";

    cout << "PROCESSING STATUS\n";
    cout << "Requests remaining in queue: "<< endingQueueSize_P << '\n';
    cout << "Requests currently processing: "<< requestsInProgress_P << '\n';
    cout << "Total unfinished requests: "<< totalUnfinishedRequests_P << '\n';
    cout << "Active/busy servers: "<< activeServers_P << '\n';
    cout << "Inactive/idle servers: "<< inactiveServers_P << "\n\n";
    cout << "STREAMING STATUS\n";
    cout << "Requests remaining in queue: "<< endingQueueSize_S << '\n';
    cout << "Requests currently processing: "<< requestsInProgress_S << '\n';
    cout << "Total unfinished requests: "<< totalUnfinishedRequests_S << '\n';
    cout << "Active/busy servers: "<< activeServers_S << '\n';
    cout << "Inactive/idle servers: "<< inactiveServers_S << "\n\n";
    cout << "COMBINED END STATUS\n";
    cout << "Total requests remaining in queues: "<< endingQueueSize << '\n';
    cout << "Total requests currently processing: "<< totalRequestsInProgress << '\n';
    cout << "Total unfinished requests: "<< totalUnfinishedRequests << '\n';
    cout << "Total active/busy servers: "<< totalActiveServers << '\n';
    cout << "Total inactive/idle servers: "<< totalInactiveServers << '\n';
    cout << "Server utilization: "<< serverUtilization << "%\n";
}
