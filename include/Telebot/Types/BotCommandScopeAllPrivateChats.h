#ifndef Telebot_BotCommandScopeAllPrivateChatsH
#define Telebot_BotCommandScopeAllPrivateChatsH

#include "Telebot/Types/BotCommandScope.h"

namespace Telebot
{
    class BotCommandScopeAllPrivateChats : public BotCommandScope
    {
    public:
        static const std::string TYPE;

        typedef std::shared_ptr<BotCommandScopeAllPrivateChats> Ptr;

        BotCommandScopeAllPrivateChats()
        {
            Type = TYPE;
        }
    };
}

#endif