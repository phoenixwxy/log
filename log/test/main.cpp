#include <iostream>

#include "types.h"

#include "plog.h"

using namespace Log;

int main(int argc, char const *argv[])
{
    /* code */

    std::cout << "test " << std::endl;

    g_PlogObj->TestProcessFunc();

    return 0;
}

