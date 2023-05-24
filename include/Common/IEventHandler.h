#ifndef Common_EventHandlerH
#define Common_EventHandlerH

#include <memory>

namespace Common
{
    template<typename ...TParams>
    class IEventHandler
    {
    public:
        IEventHandler() = default;
        virtual ~IEventHandler() = default;

        bool operator==(const IEventHandler<TParams...>& other) const
        {
            return IsEquals(other);
        }

        bool operator!=(const IEventHandler<TParams...>& other) const
        {
            return !IsEquals(other);
        }

        virtual void Call(TParams... params) = 0;

    protected:
        virtual bool IsEquals(const IEventHandler<TParams...>& other) const = 0;
    };
}

#endif