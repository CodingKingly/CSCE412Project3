#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <iostream>
#include <random>
using namespace std;

struct Request
{
    std::string IPin;
    std::string IPout;
    int totalTime;
    char jobType;
};

Request makearandomRequest();

#endif