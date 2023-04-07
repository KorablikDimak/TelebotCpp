#ifndef Telebot_ChatSharedH
#define Telebot_ChatSharedH

#include "Telebot/JsonMacros.h"

namespace Telebot
{
    class ChatShared
    {
    public:
        typedef std::shared_ptr<ChatShared> Ptr;

        std::int32_t request_id;
        std::int64_t user_id;
    };

    inline void from_json(const Json& json, ChatShared& object)
    {
        VALUE_FROM_JSON(request_id)
        VALUE_FROM_JSON(user_id)
    }
}

#endif