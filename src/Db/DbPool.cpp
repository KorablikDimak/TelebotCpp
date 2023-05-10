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
    std::lock_guard<std::mutex> lock(_queueConnectionMutex);

    if (_connections.empty() && _activeConnection < _poolSize)
        _connections.push(std::make_shared<pqxx::connection>(_connectionString));

    while (_activeConnection >= _poolSize)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

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
