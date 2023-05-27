#ifndef MyBot_DalleSettingsH
#define MyBot_DalleSettingsH

#include "Size.h"
#include "DbMacros.h"

namespace MyBot
{
    class DalleSettings
    {
    public:
        typedef std::shared_ptr<DalleSettings> Ptr;

        std::int64_t userid;
        Size size;
        bool allowvoice;
    };

    inline void FromDbRow(const pqxx::row& row, DalleSettings::Ptr& object)
    {
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