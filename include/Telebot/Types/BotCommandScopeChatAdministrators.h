#ifndef Telebot_BotCommandScopeChatAdministratorsH
#define Telebot_BotCommandScopeChatAdministratorsH

#include "Telebot/Types/BotCommandScope.h"

namespace Telebot
{
    class BotCommandScopeChatAdministrators : public BotCommandScope
    {
    public:
        static const std::string TYPE;

        typedef std::shared_ptr<BotCommandScopeChatAdministrators> Ptr;

        BotCommandScopeChatAdministrators()
        {
            Type = TYPE;
        }

        std::int64_t ChatId;
    };
}

#endif