#ifndef Common_EventH
#define Common_EventH

#include <list>
#include <shared_mutex>

#include "IEventHandler.h"

namespace Common
{
    template<typename ...TParams>
    class Event
    {
    private:
        using EventHandler = std::shared_ptr<IEventHandler<TParams...>>;
        using EventHandlerIterator = typename std::list<EventHandler>::iterator;

        std::list<EventHandler> _handlers;
        mutable std::shared_mutex _listMutex;
        EventHandlerIterator _currentIterator;
        bool _currentRemoved;

    public:
        Event() = default;
        ~Event() = default;

        void operator()(TParams... params)
        {
            _listMutex.lock_shared();
            _currentIterator = _handlers.begin();
            while (_currentIterator != _handlers.end())
            {
                _currentRemoved = false;
                _listMutex.unlock_shared();
                (*_currentIterator)->Call(params...);
                _listMutex.lock_shared();
                if (!_currentRemoved)
                    ++_currentIterator;
            }
            _listMutex.unlock_shared();
        }

        void operator+=(const EventHandler& handler)
        {
            std::lock_guard<std::shared_mutex> lock(_listMutex);
            if (!Contains(handler))
                _handlers.push_back(handler);
        }

        void operator-=(const EventHandler& handler)
        {
            std::lock_guard<std::shared_mutex> lock(_listMutex);
            EventHandlerIterator iterator = Find(handler);
            if (iterator != _handlers.end())
            {
                if (_currentIterator == iterator)
                {
                    _currentRemoved = true;
                    _currentIterator = _handlers.erase(iterator);
                }
                else
                    _handlers.erase(iterator);
            }
        }

    private:
        bool Contains(const EventHandler& handler) const
        {
            for (const EventHandler& element : _handlers)
                if (*handler == *element) return true;
            return false;
        }

        EventHandlerIterator Find(const EventHandler& handler) const
        {
            for (EventHandlerIterator iterator = _handlers.begin(); iterator != _handlers.end(); ++iterator)
                if (**iterator == *handler) return iterator;
            return _handlers.end();
        }
    };
}

#endif