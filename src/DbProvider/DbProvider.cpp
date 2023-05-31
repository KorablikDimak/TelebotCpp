#include "DbProvider.h"

DbProvider::DbProvider::DbProvider(const std::string& connectionString, unsigned char poolSize)
{
    _pool = std::make_shared<DbPool>(connectionString, poolSize);
}

DbProvider::DbProvider::DbProvider(const DbPool::Ptr& pool)
{
    _pool = pool;
}