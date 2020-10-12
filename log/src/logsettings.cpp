#include "logsettings.h"

namespace Log
{

LogSettings::LogSettings(/* args */)
{
}

LogSettings::~LogSettings()
{
}

PResult LogSettings::GetInstance()
{
    static LogSettings* pLogSettings = new LogSettings;
    if (nullptr != pLogSettings) {
        PResult result = PResultEFailed;

        result = pLogSettings->Initialize();

        if (PResultSuccess != result) {
            pLogSettings->Destroy();
            pLogSettings = nullptr;
        }
    }
}

PResult LogSettings::Initialize()
{
    // Will be check current path if has PLogSettings.txt or not
    
}

VOID LogSettings::Destroy()
{
    delete this;
}

    
} // namespace Log
