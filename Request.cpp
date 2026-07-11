#include "Request.h"



Request makearandomRequest()
{   
    //for randomIPin and randomIPout
    std::string randomIPin = "";
    std::string randomIPout = "";

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 255);

    randomIPin += to_string(distrib(gen)) + "." + to_string(distrib(gen)) + "." + to_string(distrib(gen)) + "." + to_string(distrib(gen));
    randomIPout += to_string(distrib(gen)) + "." + to_string(distrib(gen)) + "." + to_string(distrib(gen)) + "." + to_string(distrib(gen));

    // Random Completion time
    uniform_int_distribution<> randomTimeDistrib(1,100);

    int randomTotalTime = randomTimeDistrib(gen);

    //random jobtype 
    char randomJobType;
    if(rand() % 2 == 0){
        randomJobType = 'p';
    }
    else{
        randomJobType = 's';
    }

    struct Request RandomRequest = {randomIPin, randomIPout,randomTotalTime, randomJobType };

    return RandomRequest;
}