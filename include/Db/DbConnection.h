#ifndef DbProvider_DbConnectionH
#define DbProvider_DbConnectionH

#include <future>

#include "DbPool.h"

namespace DbProvider
{
    class DbConnection
    {
    private:
        DbPool::Ptr _pool;

    public:
        typedef std::shared_ptr<DbConnection> Ptr;

        explicit DbConnection(const std::string& connectionString, unsigned char poolSize = 1);
        explicit DbConnection(const DbPool::Ptr& pool);
        ~DbConnection() = default;

        template<typename TResult, typename ...TParams>
        std::future<TResult> StartTransaction(std::function<TResult(pqxx::work&, TParams...)> transaction,
                                              TParams... params)
        {
            return std::async(std::launch::async, [this, transaction](auto&&... args)->TResult
            {
                std::shared_ptr<pqxx::connection> connection = _pool->GetConnection();
                pqxx::work work{*connection};
                TResult result = transaction(work, std::forward<decltype(args)>(args)...);
                work.commit();
                _pool->ReturnInPool(connection);
                return result;
            }, params...);
        }
    };
}

#endif