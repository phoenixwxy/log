#ifndef __PHOENIX_HEADER_LOGQUEUE_H
#define __PHOENIX_HEADER_LOGQUEUE_H

#include <iostream>
#include <queue>
#include <string>

#include "types.h"
#include "utils.h"

namespace Log
{

#define MAX_LOG_QUEUE   1024

class LogQueue
{
private:
    /* data */
public:
    LogQueue(/* args */);
    ~LogQueue();

    PResult Create();
    PResult LogEnQueue(std::string logText);
    PResult LogDeQueue(std::string logText);
};



    
} // namespace Log




#endif