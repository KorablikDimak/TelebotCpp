#ifndef Telebot_BotCommandScopeAllChatAdministratorsH
#define Telebot_BotCommandScopeAllChatAdministratorsH

#include "Telebot/Types/BotCommandScope.h"

namespace Telebot
{
    class BotCommandScopeAllChatAdministrators : public BotCommandScope
    {
    public:
        static const std::string TYPE;

        typedef std::shared_ptr<BotCommandScopeAllChatAdministrators> Ptr;

        BotCommandScopeAllChatAdministrators()
        {
            Type = TYPE;
        }
    };
}

#endif