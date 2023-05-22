#include "Common/ErrorTrace.h"

void Common::ErrorTrace::Push(const ErrorInfo& errorInfo)
{
    _stackTrace.push(errorInfo);
}

Common::ErrorInfo Common::ErrorTrace::Pop()
{
    ErrorInfo errorInfo = _stackTrace.top();
    _stackTrace.pop();
    return errorInfo;
}

std::string Common::ErrorTrace::ToString()
{
    std::string result;
    std::stack<ErrorInfo> stackTrace(_stackTrace);

    unsigned short stackFrame = 0;
    while (!stackTrace.empty())
    {
        result += "stack frame:" + std::to_string(stackFrame) + "\n";

        ErrorInfo errorInfo = stackTrace.top();
        stackTrace.pop();

        switch (errorInfo.ErrorCode())
        {
            case ErrorCode::Undefined:
                result += "error code 0: Undefined\n";
                break;
            case ErrorCode::RuntimeError:
                result += "error code 1: RuntimeError\n";
                break;
            case ErrorCode::NullPointer:
                result += "error code 10: NullPointer\n";
                break;
            case ErrorCode::IncorrectArgument:
                result += "error code 20: IncorrectArgument\n";
                break;
            case ErrorCode::ParseFailed:
                result += "error code 30: ParseFailed\n";
                break;
            case ErrorCode::JsonParseFailed:
                result += "error code 31: JsonParseFailed\n";
                break;
        }

        result += errorInfo.What() + "\n";
        ++stackFrame;
    }

    return result;
}