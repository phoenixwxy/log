#include "plog.h"

struct DebugLogInfo g_logInfo =
{
    {
        0x0,        // PLogDebug
        0x3,        // PLogError
        0x0,        // PLogWarn
        0x0,        // PLogConfig
        0x3,        // PLogInfo
        0x0,        // PLogVerbose
        0x0,        // PLogDump
        0x0,        // PLogCoreCfg
    },
    nullptr,
    TRUE
};

namespace Log {

Plog* g_PlogObj = Plog::Create();


Plog* Plog::Create()
{
    static Plog* pPlog = new Plog;
    if (nullptr != pPlog) {
        PResult result = PResultSuccess;

        result = pPlog->Initialize();

        if (PResultSuccess != result) {
            pPlog->Destroy();
            pPlog = nullptr;
        }
    }

    return pPlog;
}

VOID Plog::Destroy()
{

    if (nullptr != mConfigFile) {
        delete mConfigFile;
        mConfigFile = nullptr;
    }

    if (nullptr != mLogConfigMask) {
        delete mLogConfigMask;
        mLogConfigMask = nullptr;
    }

    g_logInfo.pDebugLogFile->close();

    delete this;
}

PResult Plog::Initialize()
{
    PResult result = PResultSuccess;

    mConfigFile = new std::ifstream;
    if (nullptr == mConfigFile) {
        result = PResultEInvalidPointer;
    }

    mLogFileName = LogFileName;
    // std::cout << mLogFileName << std::endl;

    mConfigFile->open(ConfigFileName, std::ios::in);
    if (!mConfigFile->is_open()) {
        result = PResultEFailed;
    }

    ReadConfigFromFile();

    result = OverrideLogConfig(mLogConfigMask);

    // TODO record config
    // for (PLog i = 0; i < PLogMax; i++) {
    //     std::cout << g_logInfo.groupEnable[i] << std::endl;
    // }
    // std::cout << "Phoenix " << g_logInfo.pDebugEnable << std::endl;

    g_logInfo.pDebugLogFile = new std::fstream;
    g_logInfo.pDebugLogFile->open(mLogFileName, std::ios::out|std::ios::app);
    if (!g_logInfo.pDebugLogFile->is_open()) {
        result = PResultEFailed;
    }

    mConfigFile->close();
    return result;
}


PResult Plog::OverrideLogConfig(std::vector<std::string>* logConfigMask)
{
    PResult result = PResultSuccess;

    std::vector<std::string>::iterator it = logConfigMask->begin();
    for (; it != logConfigMask->end(); it++) {
        UINT num = -1;
        // std::cout << *it << std::endl;
        // std::cout << it->substr(num+1, 2) << std::endl;

        if ((num = it->find('=')) != std::string::npos) {
            if ((it->substr(num+1, 2) == "0x")) {
                UINT numMask = std::stoi(it->substr(num+3), nullptr, 16);

                if (it->substr(0, num) == "PLogDebugMask") {
                    // std::cout << "PLogDebugMask" << std::endl;
                    g_logInfo.groupEnable[PLogDebug] = numMask;
                } else if (it->substr(0, num) == "PLogErrorMask") {
                    // std::cout << "PLogErrorMask" << std::endl;
                    g_logInfo.groupEnable[PLogError] = numMask;
                } else if (it->substr(0, num) == "PLogWarnMask") {
                    // std::cout << "PLogWarnMask" << std::endl;
                    g_logInfo.groupEnable[PLogWarn] = numMask;
                } else if (it->substr(0, num) == "PLogConfigMask") {
                    // std::cout << "PLogConfigMask" << std::endl;
                    g_logInfo.groupEnable[PLogConfig] = numMask;
                } else if (it->substr(0, num) == "PLogInfoMask") {
                    // std::cout << "PLogInfoMask" << std::endl;
                    g_logInfo.groupEnable[PLogInfo] = numMask;
                } else if (it->substr(0, num) == "PLogVerboseMask") {
                    // std::cout << "PLogVerboseMask" << std::endl;
                    g_logInfo.groupEnable[PLogVerbose] = numMask;
                } else if (it->substr(0, num) == "PLogDumpMask") {
                    // std::cout << "PLogDumpMask" << std::endl;
                    g_logInfo.groupEnable[PLogDump] = numMask;
                } else if (it->substr(0, num) == "PLogCoreCfgMask") {
                    // std::cout << "PLogCoreCfgMask" << std::endl;
                    g_logInfo.groupEnable[PLogCoreCfg] = numMask;
                } else {
                    result = PResultEInvalidArg;
                }
            } else if (it->substr(0, num) == "DebugEnable") {
                if ("TRUE" == it->substr(num+1)) {
                    g_logInfo.pDebugEnable = TRUE;
                } else if ("FALSE" == it->substr(num+1)) {
                    g_logInfo.pDebugEnable = FALSE;
                } else {
                    result = PResultEInvalidArg;
                }
            } else if (it->substr(0, num) == "LogFileName") {
                std::string logFileName = it->substr(num+1);
                mLogFileName = logFileName;
            } else {
                result = PResultEInvalidArg;
            }
        } else {
            result = PResultEInvalidArg;
        }
    }

    return result;
    // std::cout << std::endl;
}

VOID Plog::ReadConfigFromFile()
{
    mLogConfigMask = new std::vector<std::string>;
    std::string buffer;

    while (!mConfigFile->eof())
    {
        buffer.clear();
        std::getline(*mConfigFile, buffer);
        mLogConfigMask->push_back(buffer);
    }
}

VOID Plog::PLogSystem(
        PLogGroup   group,
        const CHAR* pLevel,
        PLog        level,
        const CHAR* pFormat,
        ...)
{
    if (TRUE == g_logInfo.pDebugEnable) {
        CHAR logText[MaxLogLength];

        va_list args;
        va_start(args, pFormat);
        Phoenix::Utils::VSNPrintF(logText, sizeof(logText), pFormat, args);
        va_end(args);

        // std::cout << logText << std::endl;

        CHAR    finalText[MaxLogLength];
        SIZE_T  finalTextLen    = 0;

        PDateTime* pCurrentTime = new PDateTime;
        Phoenix::Utils::GetDateTime(pCurrentTime);

        if (nullptr != pCurrentTime) {
            finalTextLen = Phoenix::Utils::SNPrintF(finalText,
                sizeof(finalText),
                "%02d-%02d %02d:%02d:%02d:%09ld  %4d  %4d %s %s\n",
                (pCurrentTime->month + 1),
                pCurrentTime->dayOfMonth,
                pCurrentTime->hours,
                pCurrentTime->minutes,
                pCurrentTime->seconds,
                pCurrentTime->microseconds,
                Phoenix::Utils::GetProcessID(),
                Phoenix::Utils::GetThreadID(),
                pLevel,
                logText);
        }

        g_logInfo.pDebugLogFile->write(finalText, finalTextLen);
    }
}



VOID Plog::TestProcessFunc()
{
    int i = 0;
    do
    {
        /* code */
        i++;
        // std::cout << "i: " << i << std::endl;
    } while (i != 1);
    
}

} // end Plog class