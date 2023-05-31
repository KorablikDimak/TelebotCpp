#ifndef MyBot_DalleSettingsH
#define MyBot_DalleSettingsH

#include "OpenAI/Types/Size.h"
#include "DbProvider/DbMacros.h"

namespace MyBot
{
    class DalleSettings
    {
    public:
        typedef std::shared_ptr<DalleSettings> Ptr;

        std::int64_t userid;
        OpenAI::Size size;
        bool allowvoice;
    };

    inline void FromDbRow(const pqxx::row& row, DalleSettings::Ptr& object)
    {
        using namespace OpenAI;
        GET_VALUE(userid);
        GET_ENUM(size);
        GET_VALUE(allowvoice);
    }

    inline void FromDbResult(const pqxx::result& result, std::vector<DalleSettings::Ptr>& settings)
    {
        for (const pqxx::row& row : result)
        {
            DalleSettings::Ptr object = std::make_shared<DalleSettings>();
            FromDbRow(row, object);
            settings.push_back(object);
        }
    }
}

#endif