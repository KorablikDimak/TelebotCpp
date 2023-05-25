#ifndef Telebot_KeyboardButtonRequestUserH
#define Telebot_KeyboardButtonRequestUserH

#include "Common/JsonMacros.h"

namespace Telebot
{
    class KeyboardButtonRequestUser
    {
    public:
        typedef std::shared_ptr<KeyboardButtonRequestUser> Ptr;

        std::int32_t request_id;
        bool user_is_bot;
        bool user_is_premium;
    };

    inline void to_json(Json& json, const KeyboardButtonRequestUser::Ptr& object)
    {
        VALUE_TO_JSON(request_id)
        VALUE_TO_JSON(user_is_bot)
        VALUE_TO_JSON(user_is_premium)
    }
}

#endif