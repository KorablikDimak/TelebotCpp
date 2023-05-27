#ifndef MyBot_UserH
#define MyBot_UserH

#include "Language.h"
#include "Role.h"
#include "DbMacros.h"

namespace MyBot
{
    class User
    {
    public:
        typedef std::shared_ptr<User> Ptr;

        std::int64_t userid;
        int totalusage;
        int usagelimit;
        Language language;
        Role role;
    };

    inline void FromDbRow(const pqxx::row& row, User::Ptr& object)
    {
        GET_VALUE(userid);
        GET_VALUE(totalusage);
        GET_VALUE(usagelimit);
        GET_ENUM(language);
        GET_ENUM(role);
    }

    inline void FromDbResult(const pqxx::result& result, std::vector<User::Ptr>& users)
    {
        for (const pqxx::row& row : result)
        {
            User::Ptr object = std::make_shared<User>();
            FromDbRow(row, object);
            users.push_back(object);
        }
    }
}

#endif