#include "MyBot/DbRequest.h"

const unsigned char MyBot::DbRequest::POOL_MAX_SIZE = 3;

MyBot::DbRequest::DbRequest(const std::string& connectionString)
{
    _dbConnection = std::make_unique<DbProvider::DbConnection>(connectionString, POOL_MAX_SIZE);
}

std::future<bool> MyBot::DbRequest::IsUser(std::int64_t userId)
{
    std::function<bool(pqxx::work&, std::int64_t)> transaction =
            [](pqxx::work& work, const std::int64_t& userId)->bool
            {
                std::string query = "SELECT EXISTS(SELECT 1 FROM \"Users\" WHERE userid = " + std::to_string(userId) + ")";
                return work.query_value<bool>(query);
            };

    return _dbConnection->TransactAsync<bool, std::int64_t>(transaction, userId);
}

std::future<MyBot::User::Ptr> MyBot::DbRequest::GetUser(std::int64_t userId)
{
    std::function<User::Ptr(pqxx::work&, std::int64_t)> transaction =
            [](pqxx::work& work, const std::int64_t& userId)->User::Ptr
            {
                std::string query = "SELECT * FROM \"Users\" WHERE userid = " + std::to_string(userId);
                pqxx::result result = work.exec(query);
                pqxx::row row = result.front();

                User::Ptr user = std::make_shared<User>();
                FromDbRow(row, user);
                return user;
            };

    return _dbConnection->TransactAsync<User::Ptr, std::int64_t>(transaction, userId);
}

std::future<bool> MyBot::DbRequest::AddUser(std::int64_t userId)
{
    std::function<bool(pqxx::work&, std::int64_t)> transaction =
            [](pqxx::work& work, const std::int64_t& userId)->bool
            {
                std::string query = "INSERT INTO \"Users\" (userid) VALUES (" + std::to_string(userId) + ")";
                work.exec(query);

                query = "INSERT INTO \"GptSettings\" (userid) VALUES (" + std::to_string(userId) + ")";
                work.exec(query);

                query = "INSERT INTO \"WhisperSettings\" (userid) VALUES (" + std::to_string(userId) + ")";
                work.exec(query);

                query = "INSERT INTO \"DalleSettings\" (userid) VALUES (" + std::to_string(userId) + ")";
                work.exec(query);
                return true;
            };

    return _dbConnection->TransactAsync<bool, std::int64_t>(transaction, userId);
}

std::future<MyBot::Role> MyBot::DbRequest::GetRole(std::int64_t userId)
{
    std::function<Role(pqxx::work&, std::int64_t)> transaction =
            [](pqxx::work& work, const std::int64_t& userId)->Role
            {
                std::string query = "SELECT role FROM \"Users\" WHERE userid = " + std::to_string(userId);
                auto result = work.query_value<std::string>(query);
                Role ret;
                FromString(ret, result);
                return ret;
            };

    return _dbConnection->TransactAsync<Role, std::int64_t>(transaction, userId);
}

std::future<bool> MyBot::DbRequest::SetRole(std::int64_t userId, Role role)
{
    std::function<bool(pqxx::work&, std::int64_t, Role)> transaction =
            [](pqxx::work& work, const std::int64_t& userId, const Role& role)->bool
            {
                std::string query = "UPDATE \"Users\" SET role = '" + ToString(role) +
                                    "' WHERE userid = " + std::to_string(userId);
                work.exec(query);
                return true;
            };

    return _dbConnection->TransactAsync<bool, std::int64_t, Role>(transaction, userId, role);
}

std::future<int> MyBot::DbRequest::GetUsage(std::int64_t userId)
{
    std::function<int(pqxx::work&, std::int64_t)> transaction =
            [](pqxx::work& work, const std::int64_t& userId)->int
            {
                std::string query = "SELECT totalusage FROM \"Users\" WHERE userid = " + std::to_string(userId);
                return work.query_value<int>(query);
            };

    return _dbConnection->TransactAsync<int, std::int64_t>(transaction, userId);
}

std::future<bool> MyBot::DbRequest::AddUsage(std::int64_t userId, int usage)
{
    std::function<bool(pqxx::work&, std::int64_t, int)> transaction =
            [](pqxx::work& work, const std::int64_t& userId, const int& usage)->bool
            {
                std::string query = "UPDATE \"Users\" SET totalusage = totalusage + " + std::to_string(usage) +
                                    " WHERE userid = " + std::to_string(userId);
                work.exec(query);
                return true;
            };

    return _dbConnection->TransactAsync<bool, std::int64_t, int>(transaction, userId, usage);
}

std::future<int> MyBot::DbRequest::GetUsageLimit(std::int64_t userId)
{
    std::function<int(pqxx::work&, std::int64_t)> transaction =
            [](pqxx::work& work, const std::int64_t& userId)->int
            {
                std::string query = "SELECT usagelimit FROM \"Users\" WHERE userid = " + std::to_string(userId);
                return work.query_value<int>(query);
            };

    return _dbConnection->TransactAsync<int, std::int64_t>(transaction, userId);
}

std::future<bool> MyBot::DbRequest::SetUsageLimit(std::int64_t userId, int usageLimit)
{
    std::function<bool(pqxx::work&, std::int64_t, int)> transaction =
            [](pqxx::work& work, const std::int64_t& userId, const int& usageLimit)->bool
            {
                std::string query = "UPDATE \"Users\" SET usagelimit = " + std::to_string(usageLimit) +
                                    " WHERE userid = " + std::to_string(userId);
                work.exec(query);
                return true;
            };

    return _dbConnection->TransactAsync<bool, std::int64_t, int>(transaction, userId, usageLimit);
}

std::future<MyBot::Language> MyBot::DbRequest::GetLanguage(std::int64_t userId)
{
    std::function<Language(pqxx::work &, std::int64_t)> transaction =
            [](pqxx::work& work, const std::int64_t& userId)->Language
            {
                std::string query = "SELECT language FROM \"Users\" WHERE userid = " + std::to_string(userId);
                auto result = work.query_value<std::string>(query);
                Language ret;
                FromString(ret, result);
                return ret;
            };

    return _dbConnection->TransactAsync<Language, std::int64_t>(transaction, userId);
}

std::future<bool> MyBot::DbRequest::SetLanguage(std::int64_t userId, Language language)
{
    std::function<bool(pqxx::work&, std::int64_t, Language)> transaction =
            [](pqxx::work& work, const std::int64_t& userId, const Language& language)->bool
            {
                std::string query = "UPDATE \"Users\" SET language = '" + ToString(language) +
                                    "' WHERE userid = " + std::to_string(userId);
                work.exec(query);
                return true;
            };

    return _dbConnection->TransactAsync<bool, std::int64_t, Language>(transaction, userId, language);
}

std::future<MyBot::GptSettings::Ptr> MyBot::DbRequest::GetGptSettings(std::int64_t userId)
{
    std::function<GptSettings::Ptr(pqxx::work&, std::int64_t)> transaction =
            [](pqxx::work& work, const std::int64_t& userId)->GptSettings::Ptr
            {
                std::string query = "SELECT * FROM \"GptSettings\" WHERE userid = " + std::to_string(userId);
                pqxx::result result = work.exec(query);
                pqxx::row row = result.front();

                GptSettings::Ptr settings = std::make_shared<GptSettings>();
                FromDbRow(row, settings);
                return settings;
            };

    return _dbConnection->TransactAsync<GptSettings::Ptr, std::int64_t>(transaction, userId);
}

std::future<unsigned short> MyBot::DbRequest::GetContextSize(std::int64_t userId)
{
    std::function<unsigned short(pqxx::work&, std::int64_t)> transaction =
            [](pqxx::work& work, const std::int64_t& userId)->unsigned short
            {
                std::string query = "SELECT contextsize FROM \"GptSettings\" WHERE userid = " + std::to_string(userId);
                return work.query_value<unsigned short>(query);
            };

    return _dbConnection->TransactAsync<unsigned short, std::int64_t>(transaction, userId);
}

std::future<bool> MyBot::DbRequest::SetContextSize(std::int64_t userId, unsigned short contextSize)
{
    std::function<bool(pqxx::work&, std::int64_t, unsigned short)> transaction =
            [](pqxx::work& work, const std::int64_t& userId, const unsigned short& contextSize)->bool
            {
                std::string query = "UPDATE \"GptSettings\" SET contextsize = " + std::to_string(contextSize) +
                                    " WHERE userid = " + std::to_string(userId);
                return true;
            };

    return _dbConnection->TransactAsync<bool, std::int64_t, unsigned short>(transaction, userId, contextSize);
}

std::future<bool> MyBot::DbRequest::SetGptTemperature(std::int64_t userId, float temperature)
{
    std::function<bool(pqxx::work&, std::int64_t, float)> transaction =
            [](pqxx::work& work, const std::int64_t& userId, const float& temperature)->bool
            {
                std::string query = "UPDATE \"GptSettings\" SET temperature = " + std::to_string(temperature) +
                                    " WHERE userid = " + std::to_string(userId);
                return true;
            };

    return _dbConnection->TransactAsync<bool, std::int64_t, float>(transaction, userId, temperature);
}

std::future<bool> MyBot::DbRequest::SetGptAllowVoice(std::int64_t userId, bool allowVoice)
{
    std::function<bool(pqxx::work&, std::int64_t, bool)> transaction =
            [](pqxx::work& work, const std::int64_t& userId, const bool& allowVoice)->bool
            {
                std::string query = "UPDATE \"GptSettings\" SET allowvoice = " + std::to_string(allowVoice) +
                                    " WHERE userid = " + std::to_string(userId);
                return true;
            };

    return _dbConnection->TransactAsync<bool, std::int64_t, bool>(transaction, userId, allowVoice);
}

std::future<MyBot::WhisperSettings::Ptr> MyBot::DbRequest::GetWhisperSettings(std::int64_t userId)
{
    std::function<WhisperSettings::Ptr(pqxx::work&, std::int64_t)> transaction =
            [](pqxx::work& work, const std::int64_t& userId)->WhisperSettings::Ptr
            {
                std::string query = "SELECT * FROM \"WhisperSettings\" WHERE userid = " + std::to_string(userId);
                pqxx::result result = work.exec(query);
                pqxx::row row = result.front();

                WhisperSettings::Ptr settings = std::make_shared<WhisperSettings>();
                FromDbRow(row, settings);
                return settings;
            };

    return _dbConnection->TransactAsync<WhisperSettings::Ptr, std::int64_t>(transaction, userId);
}

std::future<bool> MyBot::DbRequest::SetWhisperTemperature(std::int64_t userId, float temperature)
{
    std::function<bool(pqxx::work&, std::int64_t, float)> transaction =
            [](pqxx::work& work, const std::int64_t& userId, const float& temperature)->bool
            {
                std::string query = "UPDATE \"WhisperSettings\" SET temperature = " + std::to_string(temperature) +
                                    " WHERE userid = " + std::to_string(userId);
                return true;
            };

    return _dbConnection->TransactAsync<bool, std::int64_t, float>(transaction, userId, temperature);
}

std::future<MyBot::DalleSettings::Ptr> MyBot::DbRequest::GetDalleSettings(std::int64_t userId)
{
    std::function<DalleSettings::Ptr(pqxx::work&, std::int64_t)> transaction =
            [](pqxx::work& work, const std::int64_t& userId)->DalleSettings::Ptr
            {
                std::string query = "SELECT * FROM \"GptSettings\" WHERE userid = " + std::to_string(userId);
                pqxx::result result = work.exec(query);
                pqxx::row row = result.front();

                DalleSettings::Ptr settings = std::make_shared<DalleSettings>();
                FromDbRow(row, settings);
                return settings;
            };

    return _dbConnection->TransactAsync<DalleSettings::Ptr, std::int64_t>(transaction, userId);
}

std::future<bool> MyBot::DbRequest::SetDalleSize(std::int64_t userId, Size size)
{
    std::function<bool(pqxx::work&, std::int64_t, Size)> transaction =
            [](pqxx::work& work, const std::int64_t& userId, const Size& size)->bool
            {
                std::string query = "UPDATE \"DalleSettings\" SET size = '" + ToString(size) +
                                    "' WHERE userid = " + std::to_string(userId);
                work.exec(query);
                return true;
            };

    return _dbConnection->TransactAsync<bool, std::int64_t, Size>(transaction, userId, size);
}

std::future<bool> MyBot::DbRequest::SetDalleAllowVoice(std::int64_t userId, bool allowVoice)
{
    std::function<bool(pqxx::work&, std::int64_t, bool)> transaction =
            [](pqxx::work& work, const std::int64_t& userId, const bool& allowVoice)->bool
            {
                std::string query = "UPDATE \"DalleSettings\" SET allowvoice = " + std::to_string(allowVoice) +
                                    " WHERE userid = " + std::to_string(userId);
                return true;
            };

    return _dbConnection->TransactAsync<bool, std::int64_t, bool>(transaction, userId, allowVoice);
}