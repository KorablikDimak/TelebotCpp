#include "Db/DbConnection.h"

DbProvider::DbConnection::DbConnection(const std::string& connectionString, unsigned char poolSize)
{
    _pool = std::make_shared<DbPool>(connectionString, poolSize);
}

DbProvider::DbConnection::DbConnection(const DbPool::Ptr& pool)
{
    _pool = pool;
}