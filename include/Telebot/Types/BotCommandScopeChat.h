#ifndef Telebot_BotCommandScopeChatH
#define Telebot_BotCommandScopeChatH

#include "BotCommandScope.h"

namespace Telebot
{
    class BotCommandScopeChat : public BotCommandScope
    {
    public:
        typedef std::shared_ptr<BotCommandScopeChat> Ptr;

        static const std::string TYPE;

        BotCommandScopeChat()
        {
            type = TYPE;
        }

        std::int64_t ChatId;
    };
}

#endif