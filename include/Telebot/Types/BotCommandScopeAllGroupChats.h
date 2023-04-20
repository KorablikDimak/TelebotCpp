#ifndef Telebot_BotCommandScopeAllGroupChatsH
#define Telebot_BotCommandScopeAllGroupChatsH

#include "BotCommandScope.h"

namespace Telebot
{
    class BotCommandScopeAllGroupChats : public BotCommandScope
    {
    public:
        typedef std::shared_ptr<BotCommandScopeAllGroupChats> Ptr;

        static const std::string TYPE;

        BotCommandScopeAllGroupChats()
        {
            type = TYPE;
        }
    };
}

#endif