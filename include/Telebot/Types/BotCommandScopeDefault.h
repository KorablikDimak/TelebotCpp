#ifndef Telebot_BotCommandScopeDefaultH
#define Telebot_BotCommandScopeDefaultH

#include "Telebot/Types/BotCommandScope.h"

namespace Telebot
{
    class BotCommandScopeDefault : public BotCommandScope
    {
    public:
        static const std::string TYPE;

        typedef std::shared_ptr<BotCommandScopeDefault> Ptr;

        BotCommandScopeDefault()
        {
            Type = TYPE;
        }
    };
}

#endif