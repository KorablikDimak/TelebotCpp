#ifndef Telebot_BotCommandScopeChatH
#define Telebot_BotCommandScopeChatH

#include "Telebot/Types/BotCommandScope.h"

namespace Telebot
{
    class BotCommandScopeChat : public BotCommandScope
    {
    public:
        static const std::string TYPE;

        typedef std::shared_ptr<BotCommandScopeChat> Ptr;

        BotCommandScopeChat()
        {
            Type = TYPE;
        }

        std::int64_t ChatId;
    };
}

#endif