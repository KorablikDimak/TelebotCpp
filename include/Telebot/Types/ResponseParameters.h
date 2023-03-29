#ifndef Telebot_ResponseParametersH
#define Telebot_ResponseParametersH

#include <memory>

namespace Telebot
{
    class ResponseParameters
    {
    public:
        typedef std::shared_ptr<ResponseParameters> Ptr;

        std::int64_t MigrateToChatId;
        std::int32_t RetryAfter;
    };
}

#endif