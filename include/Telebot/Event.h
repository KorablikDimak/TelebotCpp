#ifndef Telebot_EventH
#define Telebot_EventH

#include <list>

#include "IEventHandler.h"

namespace Telebot
{
    template<typename ...TParams>
    class Event
    {
    private:
        std::list<std::shared_ptr<IEventHandler<TParams...>>> _handlers;

    public:
        Event() = default;
        virtual ~Event() = default;

        void operator()(TParams... params)
        {
            for (std::shared_ptr<IEventHandler<TParams...>> handler : _handlers)
                handler->Call(params...);
        }

        void operator+=(std::shared_ptr<IEventHandler<TParams...>> handler)
        {
            _handlers.push_back(handler);
        }
    };
}

#endif