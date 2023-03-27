#ifndef Telebot_VideoChatScheduledH
#define Telebot_VideoChatScheduledH

#include <memory>

namespace Telebot
{
    class VideoChatScheduled
    {
    public:
        typedef std::shared_ptr<VideoChatScheduled> Ptr;

        std::int32_t StartDate;
    };
}

#endif