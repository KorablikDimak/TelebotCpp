#ifndef Common_ErrorCodeH
#define Common_ErrorCodeH

namespace Common
{
    enum class ErrorCode
    {
        Undefined = 0,
        RuntimeError = 1,

        NullPointer = 10,

        IncorrectArgument = 20,

        ParseFailed = 30,
        JsonParseFailed = 31
    };
}

#endif