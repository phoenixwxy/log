#include <iostream>

#include "types.h"

#include "plog.h"

// using namespace Log;

int main(int argc, char const *argv[])
{
    /* code */

    std::cout << "test " << std::endl;

    Log::g_PlogObj->TestProcessFunc();

    PLOG_INFO(PLogGroupCore, "test");
    PLOG_CONFIG(PLogGroupCore, "2");
    PLOG_CORECFG(PLogGroupCore, "3");
    // PLOG_DEBUG(PLogGroupCore, "4");
    // PLOG_DUMP(PLogGroupCore, "5");
    PLOG_ERROR(PLogGroupCore, "6");
    // PLOG_VERBOSE(PLogGroupCore, "7");
    // PLOG_WARN(PLogGroupCore, "8");

    Log::g_PlogObj->Destroy();

    return 0;
}

