#ifndef Telebot_MethodHandlerH
#define Telebot_MethodHandlerH

#include "IEventHandler.h"

namespace Telebot
{
    template<typename TObject, typename ...TParams>
    class MethodHandler : public IEventHandler<TParams...>
    {
    private:
        TObject* _object;
        void (TObject::*_method)(TParams... params);

    public:
        MethodHandler(TObject* object, void(TObject::*method)(TParams...))
        {
            _object = object;
            _method = method;
        }

        virtual ~MethodHandler() = default;

        void Call(TParams... params) override
        {
            if (_object != nullptr)
                (_object->*_method)(params...);
        }
    };

    template<typename TObject, typename ...TParams>
    std::shared_ptr<IEventHandler<TParams...>> CreateMethodHandler(TObject* object, void(TObject::*method)(TParams...))
    {
        return std::shared_ptr<IEventHandler<TParams...>>(new MethodHandler<TObject, TParams...>(object, method));
    }
}

#define METHOD_HANDLER(object, method) Telebot::CreateMethodHandler(object, method)
#define THIS_METHOD_HANDLER(method) METHOD_HANDLER(this, method)

#endif