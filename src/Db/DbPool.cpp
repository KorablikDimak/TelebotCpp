#include "Db/DbPool.h"

DbProvider::DbPool::DbPool(const std::string& connectionString, unsigned char pollSize)
{
    _connectionString = connectionString;
    _poolSize = pollSize;
    _activeConnection = 0;
}

bool DbProvider::DbPool::IsEmpty()
{
    return _connections.empty();
}

std::shared_ptr<pqxx::connection> DbProvider::DbPool::GetConnection()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(_queueConnectionMutex);
        if (_activeConnection < _poolSize) break;
        lock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    
    std::lock_guard<std::mutex> lock(_queueConnectionMutex);

    if (_connections.empty() && _activeConnection < _poolSize)
        _connections.push(std::make_shared<pqxx::connection>(_connectionString));

    ++_activeConnection;
    std::shared_ptr<pqxx::connection> connection = _connections.front();
    _connections.pop();
    return connection;
}

void DbProvider::DbPool::ReturnInPool(const std::shared_ptr<pqxx::connection>& connection)
{
    std::lock_guard<std::mutex> lock(_queueConnectionMutex);

    if (_activeConnection > 0)
    {
        --_activeConnection;
        _connections.push(connection);
    }
}
