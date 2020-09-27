#ifndef __PHOENIX_HEADER_LOG_H
#define __PHOENIX_HEADER_LOG_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <stdarg.h>

#include "types.h"
#include "utils.h"

///////////////////////////////////////////////////////////////////////////////
/// PLog is simple log system
/// Please create PLog configuration file named "PLogSettings.txt"
/// if you want to set Log level.
/// PLogErrorMask=0x3 means all goup will be enable Error Mask
///////////////////////////////////////////////////////////////////////////////

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

extern Plog* g_PlogObj;




} // End namespace Log

#define PLOG(levelchar, level, levelString, group, fmt, ...)                    \
    Log::Plog::PLogSystem(                                                      \
        group,                                                                  \
        levelchar,                                                              \
        (level),                                                                \
        levelString "%s %s:" PLOG_STRINGIZE_MACRO(__LINE__) " %s() " fmt,      \
        Log::Plog::GroupToString(group),                                        \
        Phoenix::Utils::GetFileName(__FILE__),                                  \
        __FUNCTION__,                                                           \
        ##__VA_ARGS__);
    
// PLogDebug  
// PLogError  
// PLogWarn   
// PLogConfig 
// PLogInfo   
// PLogVerbose
// PLogDump   
// PLogCoreCfg
// PLogMax    

#define PLOG_INFO(group, fmt, ...)                                              \
    if (g_logInfo.groupEnable[PLogInfo] & group)                                \
        PLOG("I", PLogInfo, "[INFO    ]", group, fmt, ##__VA_ARGS__)

#define PLOG_DEBUG(group, fmt, ...)                                             \
    if (g_logInfo.groupEnable[PLogDebug] & group)                               \
        PLOG("D", PLogDebug, "[DEBUG   ]", group, fmt, ##__VA_ARGS__)

#define PLOG_ERROR(group, fmt, ...)                                             \
        PLOG("E", PLogError, "[ERROR   ]", group, fmt, ##__VA_ARGS__)

#define PLOG_CONFIG(group, fmt, ...)                                            \
    if (g_logInfo.groupEnable[PLogConfig] & group)                              \
        PLOG("I", PLogConfig, "[CONFIG  ]", group, fmt, ##__VA_ARGS__)

#define PLOG_WARN(group, fmt, ...)                                              \
    if (g_logInfo.groupEnable[PLogWarn] & group)                                \
        PLOG("W", PLogWarn, "[WARN    ]", group, fmt, ##__VA_ARGS__)

#define PLOG_VERBOSE(group, fmt, ...)                                           \
    if (g_logInfo.groupEnable[PLogVerbose] & group)                             \
        PLOG("V", PLogVerbose, "[VERBOSE ]", group, fmt, ##__VA_ARGS__)

#define PLOG_DUMP(group, fmt, ...)                                              \
    if (g_logInfo.groupEnable[PLogDump] & group)                                \
        PLOG("D", PLogDump, "[DUMP    ]", group, fmt, ##__VA_ARGS__)

#define PLOG_CORECFG(group, fmt, ...)                                              \
    if (g_logInfo.groupEnable[PLogCoreCfg] & group)                                \
        PLOG("I", PLogCoreCfg, "[CORE_CFG]", group, fmt, ##__VA_ARGS__)

#endif