#ifndef Telebot_EventHandlerH
#define Telebot_EventHandlerH

#include <memory>

namespace Telebot
{
    template<typename ...TParams>
    class IEventHandler
    {
    public:
        IEventHandler() = default;
        virtual ~IEventHandler() = default;

        virtual void Call(TParams... params) = 0;
    };
}

#endif