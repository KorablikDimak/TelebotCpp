#ifndef Telebot_BotCommandScopeH
#define Telebot_BotCommandScopeH

#include <memory>
#include <string>

namespace Telebot
{
    class BotCommandScope
    {
    public:
        typedef std::shared_ptr<BotCommandScope> Ptr;

        BotCommandScope() = default;
        virtual ~BotCommandScope() = default;

        std::string Type;
    };
}

#endif