#ifndef Common_StaticMethodHandlerH
#define Common_StaticMethodHandlerH

#include "IEventHandler.h"

namespace Common
{
    template<typename ...TParams>
    class StaticMethodHandler : public IEventHandler<TParams...>
    {
    private:
        void (*_method)(TParams... params);

    public:
        explicit StaticMethodHandler(void(*method)(TParams...))
        {
            _method = method;
        }

        virtual ~StaticMethodHandler() = default;

        void Call(TParams... params) override
        {
            *_method(params...);
        }
    };

    template<typename ...TParams>
    std::shared_ptr<IEventHandler<TParams...>> CreateStaticMethodHandler(void(*method)(TParams...))
    {
        return std::shared_ptr<IEventHandler<TParams...>>(new StaticMethodHandler<TParams...>(method));
    }
}

#define STATIC_METHOD_HANDLER(method) Common::CreateStaticMethodHandler(method);

#endif