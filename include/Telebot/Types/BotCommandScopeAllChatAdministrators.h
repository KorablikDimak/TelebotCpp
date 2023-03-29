#ifndef Telebot_BotCommandScopeAllChatAdministratorsH
#define Telebot_BotCommandScopeAllChatAdministratorsH

#include "BotCommandScope.h"

namespace Telebot
{
    class BotCommandScopeAllChatAdministrators : public BotCommandScope
    {
    public:
        typedef std::shared_ptr<BotCommandScopeAllChatAdministrators> Ptr;

        static const std::string TYPE;

        BotCommandScopeAllChatAdministrators()
        {
            Type = TYPE;
        }
    };
}

#endif