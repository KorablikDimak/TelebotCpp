#ifndef Telebot_KeyboardButtonPollTypeH
#define Telebot_KeyboardButtonPollTypeH

#include "Common/JsonMacros.h"

namespace Telebot
{
    class KeyboardButtonPollType
    {
    public:
        typedef std::shared_ptr<KeyboardButtonPollType> Ptr;

        std::string type;
    };

    inline void to_json(Json& json, const KeyboardButtonPollType::Ptr& object)
    {
        VALUE_TO_JSON(type)
    }
}

#endif