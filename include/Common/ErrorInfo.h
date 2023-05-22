#ifndef Common_ErrorInfoH
#define Common_ErrorInfoH

#include <string>
#include <memory>

#include "ErrorCode.h"

namespace Common
{
    class ErrorInfo
    {
    private:
        ErrorCode _errorCode;
        std::string _description;

    public:
        typedef std::shared_ptr<ErrorInfo> Ptr;

        ErrorInfo(ErrorCode errorCode, const std::string& description);
        ~ErrorInfo() = default;

        ErrorCode ErrorCode();
        std::string What();
    };
}

#endif