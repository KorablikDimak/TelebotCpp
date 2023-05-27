#ifndef Common_MethodHandlerH
#define Common_MethodHandlerH

#include "IEventHandler.h"

namespace Common
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

        bool IsEquals(TObject* object, void(TObject::*method)(TParams...)) const
        {
            return _object == object && _method == method;
        }

    protected:
        bool IsEquals(const IEventHandler<TParams...>& other) const override
        {
            const auto* methodHandler = static_cast<const MethodHandler<TObject, TParams...>*>(&other);
            return methodHandler->IsEquals(_object, _method);
        }
    };

    template<typename TObject, typename ...TParams>
    std::shared_ptr<IEventHandler<TParams...>> CreateMethodHandler(TObject* object, void(TObject::*method)(TParams...))
    {
        return std::shared_ptr<IEventHandler<TParams...>>(new MethodHandler<TObject, TParams...>(object, method));
    }
}

#define METHOD_HANDLER(object, method) \
Common::CreateMethodHandler(object, method)

#define THIS_METHOD_HANDLER(method) \
METHOD_HANDLER(this, method)

#endif