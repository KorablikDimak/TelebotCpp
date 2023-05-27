#ifndef MyBot_GptSettingsH
#define MyBot_GptSettingsH

#include "DbMacros.h"

namespace MyBot
{
    class GptSettings
    {
    public:
        typedef std::shared_ptr<GptSettings> Ptr;

        std::int64_t userid;
        unsigned short contextsize;
        float temperature;
        bool allowvoice;
    };

    inline void FromDbRow(const pqxx::row& row, GptSettings::Ptr& object)
    {
        GET_VALUE(userid);
        GET_VALUE(contextsize);
        GET_VALUE(temperature);
        GET_VALUE(allowvoice);
    }

    inline void FromDbResult(const pqxx::result& result, std::vector<GptSettings::Ptr>& settings)
    {
        for (const pqxx::row& row : result)
        {
            GptSettings::Ptr object = std::make_shared<GptSettings>();
            FromDbRow(row, object);
            settings.push_back(object);
        }
    }
}

#endif