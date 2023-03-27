#ifndef Telebot_VideoChatEndedH
#define Telebot_VideoChatEndedH

#include <memory>

namespace Telebot
{
    class VideoChatEnded
    {
    public:
        typedef std::shared_ptr<VideoChatEnded> Ptr;

        std::int32_t Duration;
    };
}

#endif