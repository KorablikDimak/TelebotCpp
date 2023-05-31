#ifndef MyBot_WhisperSettingsH
#define MyBot_WhisperSettingsH

#include "DbProvider/DbMacros.h"

namespace MyBot
{
    class WhisperSettings
    {
    public:
        typedef std::shared_ptr<WhisperSettings> Ptr;

        std::int64_t userid;
        float temperature;
    };

    inline void FromDbRow(const pqxx::row& row, WhisperSettings::Ptr& object)
    {
        GET_VALUE(userid);
        GET_VALUE(temperature);
    }

    inline void FromDbResult(const pqxx::result& result, std::vector<WhisperSettings::Ptr>& settings)
    {
        for (const pqxx::row& row : result)
        {
            WhisperSettings::Ptr object = std::make_shared<WhisperSettings>();
            FromDbRow(row, object);
            settings.push_back(object);
        }
    }
}

#endif