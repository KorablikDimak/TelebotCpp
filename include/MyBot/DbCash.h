#ifndef MyBot_DbCashH
#define MyBot_DbCashH

#include "DbRequest.h"

namespace MyBot
{
    class DbCash
    {
    private:
        DbRequest::Ptr _dbRequest;

        std::map<std::int64_t, User::Ptr> _users;
        std::map<std::int64_t, GptSettings::Ptr> _gptSettings;
        std::map<std::int64_t, WhisperSettings::Ptr> _whisperSettings;
        std::map<std::int64_t, DalleSettings::Ptr> _dalleSettings;

    public:
        typedef std::shared_ptr<DbCash> Ptr;

        explicit DbCash(const DbRequest::Ptr& request);
        ~DbCash() = default;

        User::Ptr GetUserCash(std::int64_t userId);
        std::future<bool> AddTotalUsageCash(std::int64_t userId, int usage);
        std::future<bool> SetUsageLimitCash(std::int64_t userId, int usage);
        std::future<bool> SetLanguageCash(std::int64_t userId, Language language);
        std::future<bool> SetRoleCash(std::int64_t userId, Role role);

        GptSettings::Ptr GetGptSettingsCash(std::int64_t userId);
        std::future<bool> SetContextSizeCash(std::int64_t userId, unsigned char contextSize);
        std::future<bool> SetGptTemperatureCash(std::int64_t userId, float temperature);
        std::future<bool> SetGptAllowVoiceCash(std::int64_t userId, bool allowVoice);

        WhisperSettings::Ptr GetWhisperSettingsCash(std::int64_t userId);
        std::future<bool> SetWhisperTemperatureCash(std::int64_t userId, float temperature);

        DalleSettings::Ptr GetDalleSettingsCash(std::int64_t userId);
        std::future<bool> SetDalleSizeCash(std::int64_t userId, Size size);
        std::future<bool> SetDalleAllowVoiceCash(std::int64_t userId, bool allowVoice);

        void Clear();
    };
}

#endif