#ifndef MyBot_DbRequestH
#define MyBot_DbRequestH

#include "Db/DbConnection.h"
#include "Types/User.h"
#include "Types/GptSettings.h"
#include "Types/WhisperSettings.h"
#include "Types/DalleSettings.h"

namespace MyBot
{
    class DbRequest
    {
    private:
        static const unsigned char POOL_MAX_SIZE;

        std::unique_ptr<DbProvider::DbConnection> _dbConnection;

    public:
        typedef std::shared_ptr<DbRequest> Ptr;

        explicit DbRequest(const std::string& connectionString);
        ~DbRequest() = default;

        std::future<bool> IsUser(std::int64_t userId);
        std::future<User::Ptr> GetUser(std::int64_t userId);
        std::future<bool> AddUser(std::int64_t userId);
        std::future<Role> GetRole(std::int64_t userId);
        std::future<bool> SetRole(std::int64_t userId, Role role);
        std::future<int> GetUsage(std::int64_t userId);
        std::future<bool> AddUsage(std::int64_t userId, int usage);
        std::future<int> GetUsageLimit(std::int64_t userId);
        std::future<bool> SetUsageLimit(std::int64_t userId, int usageLimit);
        std::future<Language> GetLanguage(std::int64_t userId);
        std::future<bool> SetLanguage(std::int64_t userId, Language language);

        std::future<GptSettings::Ptr> GetGptSettings(std::int64_t userId);
        std::future<unsigned short> GetContextSize(std::int64_t userId);
        std::future<bool> SetContextSize(std::int64_t userId, unsigned short contextSize);
        std::future<bool> SetGptTemperature(std::int64_t userId, float temperature);
        std::future<bool> SetGptAllowVoice(std::int64_t userId, bool allowVoice);

        std::future<WhisperSettings::Ptr> GetWhisperSettings(std::int64_t userId);
        std::future<bool> SetWhisperTemperature(std::int64_t userId, float temperature);

        std::future<DalleSettings::Ptr> GetDalleSettings(std::int64_t userId);
        std::future<bool> SetDalleSize(std::int64_t userId, Size size);
        std::future<bool> SetDalleAllowVoice(std::int64_t userId, bool allowVoice);
    };

    inline std::string ToString(bool value)
    {
        if (value) return "true";
        else return "false";
    }
}

#endif