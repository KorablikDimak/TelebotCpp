#ifndef Telebot_MessageAutoDeleteTimerChangedH
#define Telebot_MessageAutoDeleteTimerChangedH

#include "Telebot/JsonMacros.h"

namespace Telebot
{
    class MessageAutoDeleteTimerChanged
    {
    public:
        typedef std::shared_ptr<MessageAutoDeleteTimerChanged> Ptr;

        std::int32_t message_auto_delete_time;
    };

    inline void from_json(const Json& json, MessageAutoDeleteTimerChanged& object)
    {
        VALUE_FROM_JSON(message_auto_delete_time)
    }
}

#endif