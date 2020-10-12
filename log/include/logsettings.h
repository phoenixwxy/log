#ifndef __PHOENIX_HEADER_LOGSETTINGS_H
#define __PHOENIX_HEADER_LOGSETTINGS_H

#include <iostream>
#include <queue>
// #include <filesystem>

#include "types.h"
#include "utils.h"


namespace Log
{

class LogSettings
{
private:
    /* data */


    /* func */
    LogSettings(/* args */);
    ~LogSettings();

    PResult Initialize();
    VOID Destroy();
public:
    PResult GetInstance();
    
};


    
} // namespace Log



#endif