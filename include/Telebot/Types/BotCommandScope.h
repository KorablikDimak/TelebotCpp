#ifndef Telebot_BotCommandScopeH
#define Telebot_BotCommandScopeH

#include "Common/JsonMacros.h"

namespace Telebot
{
    class BotCommandScope
    {
    public:
        typedef std::shared_ptr<BotCommandScope> Ptr;

        BotCommandScope() = default;
        virtual ~BotCommandScope() = default;

        std::string type;
    };

    inline void to_json(Json& json, const BotCommandScope& object)
    {
        VALUE_TO_JSON(type)
    }
}

#endif