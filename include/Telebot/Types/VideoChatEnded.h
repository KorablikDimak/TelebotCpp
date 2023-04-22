#ifndef Telebot_VideoChatEndedH
#define Telebot_VideoChatEndedH

#include "Common/JsonMacros.h"

namespace Telebot
{
    class VideoChatEnded
    {
    public:
        typedef std::shared_ptr<VideoChatEnded> Ptr;

        std::int32_t duration;
    };

    inline void from_json(const Json& json, VideoChatEnded& object)
    {
        VALUE_FROM_JSON(duration)
    }
}

#endif