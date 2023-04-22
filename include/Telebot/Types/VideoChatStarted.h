#ifndef Telebot_VideoChatStartedH
#define Telebot_VideoChatStartedH

#include "Common/JsonMacros.h"

namespace Telebot
{
    class VideoChatStarted
    {
    public:
        typedef std::shared_ptr<VideoChatStarted> Ptr;
    };

    inline void from_json(const Json& json, VideoChatStarted& object) {}
}

#endif