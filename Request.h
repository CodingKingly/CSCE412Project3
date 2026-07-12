/**
 * @file Request.h
 * @brief Declares the Request structure and random request generator.
 * @author Abel Asteway
 * @date 2026
 */

#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <iostream>
#include <random>
using namespace std;

/**
 * @struct Request
 * @brief Represents one request handled by the load-balancing system.
 *
 * Each request contains incoming and outgoing IP addresses, the number
 * of clock cycles required for processing, and a job type.
 */
struct Request
{
    std::string IPin;
    std::string IPout;
    int totalTime;
    char jobType;
};

/**
 * @brief Generates a request containing randomized values.
 *
 * The generated request contains random incoming and outgoing IPv4
 * addresses, a random processing time, and a random job type.
 *
 * @return A randomly generated Request object.
 */
Request makearandomRequest();

#endif