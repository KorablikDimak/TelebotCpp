#ifndef Telebot_UserSharedH
#define Telebot_UserSharedH

#include "Telebot/JsonMacros.h"

namespace Telebot
{
    class UserShared
    {
    public:
        typedef std::shared_ptr<UserShared> Ptr;

        std::int32_t request_id;
        std::int64_t user_id;
    };

    inline void from_json(const Json& json, UserShared& object)
    {
        VALUE_FROM_JSON(request_id)
        VALUE_FROM_JSON(user_id)
    }
}

#endif