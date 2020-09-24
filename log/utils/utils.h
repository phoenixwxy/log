#ifndef __PHOENIX_HEADER_UTILS_H
#define __PHOENIX_HEADER_UTILS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

#include <string.h>
#include <stdarg.h>

// Linux
#include <sys/time.h>
#include <unistd.h>
#include <sys/syscall.h>

#define gettid() syscall(SYS_gettid)

#include "types.h"

namespace Phoenix {

class Utils
{
public:
    
///////////////////////////////////////////////////////////////////////////////
/// File Operations
///////////////////////////////////////////////////////////////////////////////
    static const CHAR* GetFileName(
        const CHAR* pFilePath);

    static inline const CHAR* StrRChr(
        const CHAR*      pSrc,
        CHAR             character)
    {
        return strrchr(pSrc, static_cast<INT>(character));
        // std::string buffer;
        // buffer = pSrc->substr(0, pSrc->find_last_of(character));
        // CHAR tmpbuf[] = buffer.c_str();
        // return buffer.c_str();
    }

    static inline INT VSNPrintF(
        CHAR*       pDst,
        SIZE_T      sizeDst,
        const CHAR* pFormat,
        va_list     argptr)
    {
        INT numCharWritten = 0;
        numCharWritten = vsnprintf(pDst, sizeDst, pFormat, argptr);
        return numCharWritten;
    }

    static inline INT SNPrintF(
        CHAR*       pDst,
        SIZE_T      sizeDst,
        const CHAR* pFormat,
                    ...)
    {
        INT     numCharWritten;
        va_list args;

        va_start(args, pFormat);
        numCharWritten = VSNPrintF(pDst, sizeDst, pFormat, args);
        va_end(args);

        return numCharWritten;
    }

    static VOID GetTime(PTime* pTime);

    static VOID GetDateTime(PDateTime* pDateTime);

    static UINT GetThreadID();

    static UINT GetProcessID();

    // vector<string> str_vec; print_vec(str_vec);
    template <typename T>
    static void printVector(std::vector<T>* vec)
    {
        // std::cout << "Print vector<" << typeid(vec).name() << ">" << std::endl;
        std::cout << "print vector: ";
        typename std::vector<T>::iterator iter = vec->begin();
        while (iter != vec->end()) {
            std::cout << *iter++ << "  ";
        }
        std::cout << std::endl;
    }

    template <typename T>
    static void printVector(std::vector<T> &vec)
    {
        std::cout << "打印vector: ";
        typename std::vector<T>::iterator iter = vec.begin();
        while (iter != vec.end()) {
            std::cout << *iter++ << "\t";
        }
        std::cout << std::endl;
    }


private:
    /* data */
    Utils(/* args */) = default;
};





}


#endif