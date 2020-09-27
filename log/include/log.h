#ifndef __PHOENIX_HEADER_LOG_H
#define __PHOENIX_HEADER_LOG_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <stdarg.h>

#include "types.h"
#include "utils.h"

typedef UINT32 PLog ;
static const PLog PLogDebug   = 0;  ///< Debug messages
static const PLog PLogError   = 1;  ///< Error messages
static const PLog PLogWarn    = 2;  ///< Warning messages
static const PLog PLogConfig  = 3;  ///< Config messages
static const PLog PLogInfo    = 4;  ///< Informational messages
static const PLog PLogVerbose = 5;  ///< Verbose messages
static const PLog PLogDump    = 6;  ///< Recovery Dump messages
static const PLog PLogCoreCfg = 7;  ///< Core Config messages
static const PLog PLogMax     = 8;  ///< Max verbosity levels

typedef UINT64 PLogGroup;
static const PLogGroup PLogGroupCore = (static_cast<UINT64>(1) << 0);
static const PLogGroup PLogGroupApp  = (static_cast<UINT64>(1) << 1);

struct DebugLogInfo
{
    PLogGroup       groupEnable[PLogMax];
    std::fstream*   pDebugLogFile;
    BOOL            pDebugEnable;
};

extern struct DebugLogInfo g_logInfo;


namespace Log {

#define PLOG_STRINGIZE(arg) #arg
#define PLOG_STRINGIZE_MACRO(arg) PLOG_STRINGIZE(arg)

static const CHAR ConfigFileDirectory[] = "./";
static const CHAR ConfigFileName[]      = "PLogSettings.txt";
static const CHAR LogFileName[]         = "PLog.log";

// extern UINT PLogDebugMask;
// extern UINT PLogErrorMask;
// extern UINT PLogWarnMask;
// extern UINT PLogConfigMask;
// extern UINT PLogInfoMask;
// extern UINT PLogVerboseMask;
// extern UINT PLogDumpMask;
// extern UINT PLogCoreCfgMask;

class Plog
{

public:

    // MAX of one log length
    static const UINT MaxLogLength = 1024;

    // Create static Plog object
    static Plog* Create();
    VOID Destroy();

    static const CHAR* GetFileName(
        const CHAR* pFilePath);

    static const CHAR* GroupToString(PLogGroup group)
    {
        const CHAR* pString = nullptr;
        switch (group) {
        case PLogGroupCore:         pString = "[CORE    ]";     break;
        case PLogGroupApp:          pString = "[APP     ]";     break;
        default:                    pString = "[UNKNOWN ]";     break;
        }
        return pString;
    }

    static VOID PLogSystem(
        PLogGroup   group,
        const CHAR* pLevel,
        PLog        level,
        const CHAR* pFormat,
        ...);
    
    VOID TestProcessFunc();
private:
    // Initialize all need resuorce
    PResult Initialize();
    // read config settings from LogConfigFile
    VOID ReadConfigFromFile();
    // Converts a human readable string to LogMaskNumber
    PResult OverrideLogConfig(std::vector<std::string>* logConfigMask);


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Log
    ///
    /// @brief Default constructor
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Plog() = default;
    Plog(const Plog&) = delete;
    Plog& operator=(const Plog&) = delete;

    /* data */
    std::ifstream*              mConfigFile;                    // Handle of LogConfigFile
    std::vector<std::string>*   mLogConfigMask;                 // Save Log config mask
    std::string                 mLogFileName;
};

extern Log::Plog* g_PlogObj;

} // End namespace Log

#endif