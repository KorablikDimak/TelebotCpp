#ifndef Telebot_ChosenInlineResultH
#define Telebot_ChosenInlineResultH

#include "Telebot/Types/User.h"
#include "Telebot/Types/Location.h"

namespace Telebot
{
    class ChosenInlineResult
    {
    public:
        typedef std::shared_ptr<ChosenInlineResult> Ptr;

        std::string ResultId;
        User::Ptr From;
        Location::Ptr Location;
        std::string InlineMessageId;
        std::string Query;
    };
}

#endif