#ifndef Telebot_ChosenInlineResultH
#define Telebot_ChosenInlineResultH

#include "User.h"
#include "Location.h"

namespace Telebot
{
    class ChosenInlineResult
    {
    public:
        typedef std::shared_ptr<ChosenInlineResult> Ptr;

        std::string result_id;
        User::Ptr from;
        Location::Ptr location;
        std::string inline_message_id;
        std::string query;
    };

    inline void from_json(const Json& json, ChosenInlineResult& object)
    {
        VALUE_FROM_JSON(result_id)
        OBJECT_FROM_JSON(from)
        OBJECT_FROM_JSON(location)
        VALUE_FROM_JSON(inline_message_id)
        VALUE_FROM_JSON(query)
    }
}

#endif