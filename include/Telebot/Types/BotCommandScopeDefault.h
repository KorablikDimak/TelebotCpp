#ifndef Telebot_BotCommandScopeDefaultH
#define Telebot_BotCommandScopeDefaultH

#include "BotCommandScope.h"

namespace Telebot
{
    class BotCommandScopeDefault : public BotCommandScope
    {
    public:
        typedef std::shared_ptr<BotCommandScopeDefault> Ptr;

        static const std::string TYPE;

        BotCommandScopeDefault()
        {
            Type = TYPE;
        }
    };
}

#endif