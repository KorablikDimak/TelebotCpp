#ifndef Common_ErrorH
#define Common_ErrorH

#include <stack>

#include "ErrorInfo.h"

namespace Common
{
    class ErrorTrace
    {
    private:
        std::stack<ErrorInfo> _stackTrace;

    public:
        typedef std::shared_ptr<ErrorTrace> Ptr;

        ErrorTrace() = default;
        ~ErrorTrace() = default;

        void Push(const ErrorInfo& errorInfo);
        ErrorInfo Pop();
        std::string ToString();
    };
}

#endif