/**
 * @file main.cpp
 * @brief Runs the processing and streaming load-balancer simulation.
 * @author Abel Asteway
 * @date 2026
 */
#include <fstream>
#include <iostream>
#include <random>
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

    cout << endl << "The load balancer is done running" << endl; 

    logFile << "PROCESSING LOAD BALANCER\n";
    logFile << "Starting queue size: "
            << startingQueueSize_P << '\n';
    logFile << "Ending queue size: "
            << endingQueueSize_P << '\n';
    logFile << "Starting web servers: "
            << startingServerCount_P << '\n';
    logFile << "Ending web servers: "
            << endingServerCount_P << '\n';
    logFile << "Web servers added: "
            << processingServersAdded << '\n';
    logFile << "Web servers deleted: "
            << processingServersDeleted << "\n\n";

    logFile << "STREAMING LOAD BALANCER\n";
    logFile << "Starting queue size: "
            << startingQueueSize_S << '\n';
    logFile << "Ending queue size: "
            << endingQueueSize_S << '\n';
    logFile << "Starting web servers: "
            << startingServerCount_S << '\n';
    logFile << "Ending web servers: "
            << endingServerCount_S << '\n';
    logFile << "Web servers added: "
            << streamingServersAdded << '\n';
    logFile << "Web servers deleted: "
            << streamingServersDeleted << "\n\n";

    logFile << "COMBINED TOTALS\n";
    logFile << "Starting queue size: "
            << startingQueueSize << '\n';
    logFile << "Ending queue size: "
            << endingQueueSize << '\n';
    logFile << "Starting web servers: "
            << startingServerCount << '\n';
    logFile << "Ending web servers: "
            << endingServerCount << '\n';
    logFile << "Total web servers added: "
            << totalServersAdded << '\n';
    logFile << "Total web servers deleted: "
            << totalServersDeleted << '\n';

    logFile.close();

    cout << "\nLOAD BALANCER SIMULATION SUMMARY\n";
    cout << "================================\n";
    cout << "Clock cycles completed: "
        << totalClockCyles << "\n\n";

    cout << "PROCESSING LOAD BALANCER\n";

    cout << "Starting queue size: "
        << startingQueueSize_P << '\n';

    cout << "Ending queue size: "
        << endingQueueSize_P << '\n';

    cout << "Starting web servers: "
        << startingServerCount_P << '\n';

    cout << "Ending web servers: "
        << endingServerCount_P << '\n';

    cout << "Web servers added: "
        << processingServersAdded << '\n';

    cout << "Web servers deleted: "
        << processingServersDeleted << "\n\n";

    cout << "STREAMING LOAD BALANCER\n";

    cout << "Starting queue size: "
        << startingQueueSize_S << '\n';

    cout << "Ending queue size: "
        << endingQueueSize_S << '\n';

    cout << "Starting web servers: "
        << startingServerCount_S << '\n';

    cout << "Ending web servers: "
        << endingServerCount_S << '\n';

    cout << "Web servers added: "
        << streamingServersAdded << '\n';

    cout << "Web servers deleted: "
        << streamingServersDeleted << "\n\n";

    cout << "COMBINED TOTALS\n";

    cout << "Starting queue size: "
        << startingQueueSize << '\n';

    cout << "Ending queue size: "
        << endingQueueSize << '\n';

    cout << "Starting web servers: "
        << startingServerCount << '\n';

    cout << "Ending web servers: "
        << endingServerCount << '\n';

    cout << "Total web servers added: "
        << totalServersAdded << '\n';

    cout << "Total web servers deleted: "
        << totalServersDeleted << '\n';
}
