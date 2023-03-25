#ifndef Telebot_LoginUrlH
#define Telebot_LoginUrlH

#include <memory>
#include <string>

namespace Telebot
{
    class LoginUrl
    {
    public:
        typedef std::shared_ptr<LoginUrl> Ptr;

        std::string Url;
        std::string ForwardText;
        std::string BotUsername;
        bool RequestWriteAccess;
    };
}

#endif