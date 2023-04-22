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

        virtual void Call(TParams... params) = 0;
    };
}

#endif