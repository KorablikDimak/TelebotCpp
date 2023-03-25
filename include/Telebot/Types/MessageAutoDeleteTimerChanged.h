#ifndef Telebot_MessageAutoDeleteTimerChangedH
#define Telebot_MessageAutoDeleteTimerChangedH

#include <memory>

namespace Telebot
{
    class MessageAutoDeleteTimerChanged
    {
    public:
        typedef std::shared_ptr<MessageAutoDeleteTimerChanged> Ptr;

        int messageAutoDeleteTime;
    };
}

#endif