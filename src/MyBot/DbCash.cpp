#include "MyBot/DbCash.h"

MyBot::DbCash::DbCash(const DbRequest::Ptr& request)
{
    _dbRequest = request;
}

MyBot::User::Ptr MyBot::DbCash::GetUserCash(std::int64_t userId)
{
    if (_users.find(userId) != _users.end()) return _users.at(userId);
    User::Ptr user = _dbRequest->GetUser(userId).get();
    _users.insert(std::make_pair(userId, user));
    return user;
}

std::future<bool> MyBot::DbCash::AddTotalUsageCash(std::int64_t userId, int usage)
{
    if (_users.find(userId) == _users.end()) GetUserCash(userId);
    _users.at(userId)->totalusage = usage;
    return _dbRequest->AddUsage(userId, usage);
}

std::future<bool> MyBot::DbCash::SetUsageLimitCash(std::int64_t userId, int usage)
{
    if (_users.find(userId) == _users.end()) GetUserCash(userId);
    _users.at(userId)->usagelimit = usage;
    return _dbRequest->SetUsageLimit(userId, usage);
}

std::future<bool> MyBot::DbCash::SetLanguageCash(std::int64_t userId, Language language)
{
    if (_users.find(userId) == _users.end()) GetUserCash(userId);
    _users.at(userId)->language = language;
    return _dbRequest->SetLanguage(userId, language);
}

std::future<bool> MyBot::DbCash::SetRoleCash(std::int64_t userId, Role role)
{
    if (_users.find(userId) == _users.end()) GetUserCash(userId);
    _users.at(userId)->role = role;
    return _dbRequest->SetRole(userId, role);
}

MyBot::GptSettings::Ptr MyBot::DbCash::GetGptSettingsCash(std::int64_t userId)
{
    if (_gptSettings.find(userId) != _gptSettings.end()) return _gptSettings.at(userId);
    GptSettings::Ptr settings = _dbRequest->GetGptSettings(userId).get();
    _gptSettings.insert(std::make_pair(userId, settings));
    return settings;
}

std::future<bool> MyBot::DbCash::SetContextSizeCash(std::int64_t userId, unsigned char contextSize)
{
    if (_gptSettings.find(userId) == _gptSettings.end()) GetGptSettingsCash(userId);
    _gptSettings.at(userId)->contextsize = contextSize;
    return _dbRequest->SetContextSize(userId, contextSize);
}

std::future<bool> MyBot::DbCash::SetGptTemperatureCash(std::int64_t userId, float temperature)
{
    if (_gptSettings.find(userId) == _gptSettings.end()) GetGptSettingsCash(userId);
    _gptSettings.at(userId)->temperature = temperature;
    return _dbRequest->SetGptTemperature(userId, temperature);
}

std::future<bool> MyBot::DbCash::SetGptAllowVoiceCash(std::int64_t userId, bool allowVoice)
{
    if (_gptSettings.find(userId) == _gptSettings.end()) GetGptSettingsCash(userId);
    _gptSettings.at(userId)->allowvoice = allowVoice;
    return _dbRequest->SetGptAllowVoice(userId, allowVoice);
}

MyBot::WhisperSettings::Ptr MyBot::DbCash::GetWhisperSettingsCash(std::int64_t userId)
{
    if (_whisperSettings.find(userId) != _whisperSettings.end()) return _whisperSettings.at(userId);
    WhisperSettings::Ptr settings = _dbRequest->GetWhisperSettings(userId).get();
    _whisperSettings.insert(std::make_pair(userId, settings));
    return settings;
}

std::future<bool> MyBot::DbCash::SetWhisperTemperatureCash(std::int64_t userId, float temperature)
{
    if (_whisperSettings.find(userId) == _whisperSettings.end()) GetWhisperSettingsCash(userId);
    _whisperSettings.at(userId)->temperature = temperature;
    return _dbRequest->SetWhisperTemperature(userId, temperature);
}

MyBot::DalleSettings::Ptr MyBot::DbCash::GetDalleSettingsCash(std::int64_t userId)
{
    if (_dalleSettings.find(userId) != _dalleSettings.end()) return _dalleSettings.at(userId);
    DalleSettings::Ptr settings = _dbRequest->GetDalleSettings(userId).get();
    _dalleSettings.insert(std::make_pair(userId, settings));
    return settings;
}

std::future<bool> MyBot::DbCash::SetDalleSizeCash(std::int64_t userId, Size size)
{
    if (_dalleSettings.find(userId) == _dalleSettings.end()) GetDalleSettingsCash(userId);
    _dalleSettings.at(userId)->size = size;
    return _dbRequest->SetDalleSize(userId, size);
}

std::future<bool> MyBot::DbCash::SetDalleAllowVoiceCash(std::int64_t userId, bool allowVoice)
{
    if (_dalleSettings.find(userId) == _dalleSettings.end()) GetDalleSettingsCash(userId);
    _dalleSettings.at(userId)->allowvoice = allowVoice;
    return _dbRequest->SetDalleAllowVoice(userId, allowVoice);
}

void MyBot::DbCash::Clear()
{
    _users.clear();
    _gptSettings.clear();
    _whisperSettings.clear();
    _dalleSettings.clear();
}