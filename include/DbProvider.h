#ifndef DbProvider_DbProviderH
#define DbProvider_DbProviderH

#include <future>

#include "DbProvider/DbPool.h"

namespace DbProvider
{
    template<typename TFunctor>
    struct FunctorResult;

    template<typename TFunctor, typename... Args>
    struct FunctorResult<TFunctor(Args...)>
    {
    public:
        typedef decltype(std::declval<TFunctor>()(std::declval<Args>()...)) ReturnType;
    };

    class DbProvider
    {
    private:
        DbPool::Ptr _pool;

    public:
        typedef std::shared_ptr<DbProvider> Ptr;

        explicit DbProvider(const std::string& connectionString, unsigned char poolSize = 1);
        explicit DbProvider(const DbPool::Ptr& pool);
        ~DbProvider() = default;

        template<typename TTransaction, typename ...TParams,
                typename TResult = typename FunctorResult<TTransaction(pqxx::work&, TParams...)>::ReturnType>
        std::future<TResult> TransactAsync(TTransaction&& transaction, TParams&&... params)
        {
            return std::async(std::launch::async, [this, transaction](auto&&... args)->TResult
            {
                std::shared_ptr<pqxx::connection> connection = _pool->GetConnection();
                pqxx::work work{*connection};
                TResult result = transaction(work, std::forward<TParams>(args)...);
                work.commit();
                _pool->ReturnInPool(connection);
                return result;
            }, params...);
        }
    };
}

#endif