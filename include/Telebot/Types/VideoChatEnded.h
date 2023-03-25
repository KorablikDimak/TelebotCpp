#ifndef Telebot_VideoChatEndedH
#define Telebot_VideoChatEndedH

#include <memory>

namespace Telebot
{
    class VideoChatEnded
    {
    public:
        typedef std::shared_ptr<VideoChatEnded> Ptr;

        int Duration;
    };
}

#endif