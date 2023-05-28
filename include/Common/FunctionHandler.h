#ifndef Common_LambdaHandlerH
#define Common_LambdaHandlerH

#include <functional>

#include "IEventHandler.h"

namespace Common
{
    template<typename ...TParams>
    class FunctionHandler : public IEventHandler<TParams...>
    {
    private:
        std::function<void(TParams...)> _function;

    public:
        explicit FunctionHandler(std::function<void(TParams...)> function)
        {
            _function = function;
        }

        virtual ~FunctionHandler() = default;

        void Call(TParams... params) override
        {
            _function(params...);
        }

        bool IsEquals(std::function<void(TParams...)> function) const
        {
            typedef void(Fn)(TParams...);
            return _function.template target<Fn*>() == function.template target<Fn*>();
        }

    protected:
        bool IsEquals(const IEventHandler<TParams...>& other) const override
        {
            const auto* functionHandler = static_cast<const FunctionHandler<TParams...>*>(&other);
            return functionHandler->IsEquals(_function);
        }
    };

    template<typename ...TParams>
    std::shared_ptr<IEventHandler<TParams...>> CreateFunctionHandler(std::function<void(TParams...)> function)
    {
        return std::shared_ptr<IEventHandler<TParams...>>(new FunctionHandler<TParams...>(function));
    }
}

#define FUNCTION_HANDLER(function) \
Common::CreateFunctionHandler(function)

#endif