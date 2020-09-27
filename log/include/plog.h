#ifndef __PHOENIX_HEADER_PLOG_H
#define __PHOENIX_HEADER_PLOG_H

#include "log.h"
#include "types.h"
#include "utils.h"

///////////////////////////////////////////////////////////////////////////////
/// PLog is simple log system
/// Please create PLog configuration file named "PLogSettings.txt"
/// if you want to set Log level.
/// PLogErrorMask=0x3 means all goup will be enable Error Mask
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/// This is all Level for log
/// PLogDebug  
/// PLogError  
/// PLogWarn   
/// PLogConfig 
/// PLogInfo   
/// PLogVerbose
/// PLogDump   
/// PLogCoreCfg
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/// Tihs is the group
/// PLogGroupCore
/// PLogGroupApp 
///////////////////////////////////////////////////////////////////////////////

extern Log::Plog* g_PlogObj;

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