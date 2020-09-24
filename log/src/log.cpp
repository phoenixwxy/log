#include "plog.h"

namespace Log {

Plog* g_PlogObj = Plog::Create();

struct DebugLogInfo g_logInfo =
{
    {
        0x0,        // PLogDebug
        0x3,        // PLogError
        0x0,        // PLogWarn
        0x0,        // PLogConfig
        0x0,        // PLogInfo
        0x0,        // PLogVerbose
        0x0,        // PLogDump
        0x3,        // PLogCoreCfg
    },
    nullptr,
    TRUE
};

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

    delete this;
}

PResult Plog::Initialize()
{
    PResult result = PResultSuccess;

    mConfigFile = new std::ifstream;
    if (nullptr == mConfigFile) {
        result = PResultEInvalidPointer;
    }

    mConfigFile->open(ConfigFileName, std::ios::in);
    if (!mConfigFile->is_open()) {
        result = PResultEFailed;
    }

    ReadConfigFromFile();

    Phoenix::Utils::printVector(mLogConfigMask);

    return result;
}

VOID Plog::ReadConfigFromFile()
{
    PResult result = PResultSuccess;

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
    
}



VOID Plog::TestProcessFunc()
{
    int i = 0;
    do
    {
        /* code */
        i++;
        std::cout << "i: " << i << std::endl;
    } while (i != 1);
    
}

} // end Plog class