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
        std::unique_ptr<std::list<std::shared_ptr<IEventHandler<TParams...>>>> _handlers;

    public:
        Event()
        {
            _handlers = std::make_unique<std::list<std::shared_ptr<IEventHandler<TParams...>>>>();
        }

        virtual ~Event() = default;

        void operator()(TParams... params)
        {
            for (std::shared_ptr<IEventHandler<TParams...>> handler : *_handlers)
                handler->Call(params...);
        }

        void operator+=(std::shared_ptr<IEventHandler<TParams...>> handler)
        {
            _handlers->push_back(handler);
        }

        bool IsEmpty()
        {
            return _handlers->empty();
        }
    };
}

#endif