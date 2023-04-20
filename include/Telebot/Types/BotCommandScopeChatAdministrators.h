#ifndef Telebot_BotCommandScopeChatAdministratorsH
#define Telebot_BotCommandScopeChatAdministratorsH

#include "BotCommandScope.h"

namespace Telebot
{
    class BotCommandScopeChatAdministrators : public BotCommandScope
    {
    public:
        typedef std::shared_ptr<BotCommandScopeChatAdministrators> Ptr;

        static const std::string TYPE;

        BotCommandScopeChatAdministrators()
        {
            type = TYPE;
        }

        std::int64_t ChatId;
    };
}

#endif