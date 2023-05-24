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
            if (!Contains(handler))
            {
                std::lock_guard<std::shared_mutex> lock(_listMutex);
                _handlers.push_back(handler);
            }
        }

        void operator-=(const EventHandler& handler)
        {
            auto iterator = Find(handler);
            std::lock_guard<std::shared_mutex> lock(_listMutex);
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

        bool IsEmpty() const
        {
            std::lock_guard<std::shared_mutex> lock(_listMutex);
            return _handlers.empty();
        }

        bool Contains(const EventHandler& handler) const
        {
            std::lock_guard<std::shared_mutex> lock(_listMutex);
            for (const EventHandler& element : _handlers)
                if (*handler == *element) return true;
            return false;
        }

        EventHandlerIterator Find(const EventHandler& handler) const
        {
            std::lock_guard<std::shared_mutex> lock(_listMutex);
            auto iterator = _handlers.begin();
            for (std::size_t i = 0; i < _handlers.size(); ++i)
                if (*_handlers.at(iterator + i) == *handler) return iterator + i;
        }
    };
}

#endif