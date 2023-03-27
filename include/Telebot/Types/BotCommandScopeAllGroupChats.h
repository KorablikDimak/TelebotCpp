#ifndef Telebot_BotCommandScopeAllGroupChatsH
#define Telebot_BotCommandScopeAllGroupChatsH

#include "Telebot/Types/BotCommandScope.h"

namespace Telebot
{
    class BotCommandScopeAllGroupChats : public BotCommandScope
    {
    public:
        static const std::string TYPE;

        typedef std::shared_ptr<BotCommandScopeAllGroupChats> Ptr;

        BotCommandScopeAllGroupChats()
        {
            Type = TYPE;
        }
    };
}

#endif