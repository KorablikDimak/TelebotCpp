#ifndef Telebot_SentWebAppMessageH
#define Telebot_SentWebAppMessageH

#include <memory>
#include <string>

namespace Telebot
{
    class SentWebAppMessage
    {
    public:
        typedef std::shared_ptr<SentWebAppMessage> Ptr;

        std::string InlineMessageId;
    };
}

#endif