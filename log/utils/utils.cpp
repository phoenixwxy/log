#include "utils.h"

namespace Phoenix {

const CHAR* Utils::GetFileName(
    const CHAR* pFilePath)
{
    const CHAR* pFileName = StrRChr(pFilePath, '/');
    if (NULL != pFileName)
    {
        // StrRChr will return a pointer to the /, advance one to the filename
        pFileName += 1;
    }
    else
    {
        pFileName = pFilePath;
    }
    return pFileName;
}

VOID Utils::GetTime(PTime* pTime)
{
    timespec time;
    clock_gettime(CLOCK_BOOTTIME, &time);

    pTime->seconds      = static_cast<UINT32>(time.tv_sec);
    pTime->nanoSeconds  = static_cast<UINT32>(time.tv_nsec);
}

VOID Utils::GetDateTime(PDateTime* pDateTime)
{
    struct timeval  timeValue;
    struct tm*      pTimeInfo   = nullptr;
    INT             result      = 0;

    result = gettimeofday(&timeValue, nullptr);
    if (0 == result)
    {
        pTimeInfo = localtime(&timeValue.tv_sec);
        if (nullptr != pTimeInfo)
        {
            pDateTime->seconds                  = static_cast<UINT32>(pTimeInfo->tm_sec);
            pDateTime->microseconds             = static_cast<UINT32>(timeValue.tv_usec);
            pDateTime->minutes                  = static_cast<UINT32>(pTimeInfo->tm_min);
            pDateTime->hours                    = static_cast<UINT32>(pTimeInfo->tm_hour);
            pDateTime->dayOfMonth               = static_cast<UINT32>(pTimeInfo->tm_mday);
            pDateTime->month                    = static_cast<UINT32>(pTimeInfo->tm_mon);
            pDateTime->year                     = static_cast<UINT32>(pTimeInfo->tm_year);
            pDateTime->weekday                  = static_cast<UINT32>(pTimeInfo->tm_wday);
            pDateTime->yearday                  = static_cast<UINT32>(pTimeInfo->tm_yday);
            pDateTime->dayLightSavingTimeFlag   = static_cast<UINT32>(pTimeInfo->tm_isdst);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OsUtils::GetThreadID
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT Utils::GetThreadID()
{
    return gettid();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OsUtils::GetProcessID
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT Utils::GetProcessID()
{
    return getpid();
}



} // end of namesppace Phoenix

