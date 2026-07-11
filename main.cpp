#include <iostream>
#include "Loadbalancer.h"
#include "Request.h"
using namespace std;

int main(){

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

    int processingServers = (numServers + 1) / 2;
    int streamingServers = numServers / 2;
    Loadbalancer S_loadBalancer;
    S_loadBalancer.loadBalancerStartServers(streamingServers);


    Loadbalancer P_loadBalancer;
    P_loadBalancer.loadBalancerStartServers( processingServers);

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
    
    int currentClockCycle = 0;

    while(currentClockCycle < totalClockCyles ){

        cout << "Clock Cycle: " << currentClockCycle << " has started" << endl
        << "There are this many S_request left " << S_loadBalancer.getRequestQueueSize() << endl <<
        "There are this many P_request left " << P_loadBalancer.getRequestQueueSize() << endl;

        cout << "-----S Cycle-----" << endl;
        S_loadBalancer.OneCylce();

        cout << "-----P Cycle-----" << endl;
        P_loadBalancer.OneCylce();
        
        if(P_loadBalancer.requestQueueempty() && S_loadBalancer.requestQueueempty()){
                cout << "all request are complete!" << endl;
                break;
        }

        currentClockCycle++;
    }
    
    cout << endl << "The load balancer is done running" << endl; 
}
