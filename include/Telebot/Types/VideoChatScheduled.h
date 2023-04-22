#ifndef Telebot_VideoChatScheduledH
#define Telebot_VideoChatScheduledH

#include "Common/JsonMacros.h"

namespace Telebot
{
    class VideoChatScheduled
    {
    public:
        typedef std::shared_ptr<VideoChatScheduled> Ptr;

        std::int32_t start_date;
    };

    inline void from_json(const Json& json, VideoChatScheduled& object)
    {
        VALUE_FROM_JSON(start_date)
    }
}

#endif