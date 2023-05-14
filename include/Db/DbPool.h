#ifndef DbProvider_DbPoolH
#define DbProvider_DbPoolH

#include <queue>
#include <mutex>
#include <thread>
#include <chrono>
#include <pqxx/pqxx>

namespace DbProvider
{
    class DbPool
    {
    private:
        std::string _connectionString;
        unsigned char _poolSize;
        unsigned char _activeConnection;
        std::queue<std::shared_ptr<pqxx::connection>> _connections;
        std::mutex _queueConnectionMutex;

    public:
        typedef std::shared_ptr<DbPool> Ptr;

        explicit DbPool(const std::string& connectionString, unsigned char poolSize = 1);
        ~DbPool() = default;

        bool IsEmpty();
        std::shared_ptr<pqxx::connection> GetConnection();
        void ReturnInPool(const std::shared_ptr<pqxx::connection>& connection);
    };
}

#endif