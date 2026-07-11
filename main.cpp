#include <iostream>
#include "Loadbalancer.h"
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


    Loadbalancer loadBalancer;
    loadBalancer.loadBalancerStartCycle(totalClockCyles);
    loadBalancer.loadBalancerStartServers(numServers);
    loadBalancer.loadBalancerStartRequest();

    loadBalancer.loadbalancerStart();

    cout << endl << "The load balancer is done running" << endl; 
}
