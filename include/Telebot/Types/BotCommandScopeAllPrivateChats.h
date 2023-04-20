#ifndef Telebot_BotCommandScopeAllPrivateChatsH
#define Telebot_BotCommandScopeAllPrivateChatsH

#include "BotCommandScope.h"

namespace Telebot
{
    class BotCommandScopeAllPrivateChats : public BotCommandScope
    {
    public:
        typedef std::shared_ptr<BotCommandScopeAllPrivateChats> Ptr;

        static const std::string TYPE;

        BotCommandScopeAllPrivateChats()
        {
            type = TYPE;
        }
    };
}

#endif