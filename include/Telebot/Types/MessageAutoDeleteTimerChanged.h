#ifndef Telebot_MessageAutoDeleteTimerChangedH
#define Telebot_MessageAutoDeleteTimerChangedH

#include <memory>

namespace Telebot
{
    class MessageAutoDeleteTimerChanged
    {
    public:
        typedef std::shared_ptr<MessageAutoDeleteTimerChanged> Ptr;

        std::int32_t MessageAutoDeleteTime;
    };
}

#endif