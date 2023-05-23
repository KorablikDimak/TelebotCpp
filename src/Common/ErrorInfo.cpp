#include "Common/ErrorInfo.h"

Common::ErrorInfo::ErrorInfo(Common::ErrorCode errorCode, const std::string& description)
{
    _errorCode = errorCode;
    _description = description;
}

Common::ErrorCode Common::ErrorInfo::ErrorCode()
{
    return _errorCode;
}

std::string Common::ErrorInfo::What()
{
    return _description;
}