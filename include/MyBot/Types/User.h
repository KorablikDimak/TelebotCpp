#ifndef MyBot_UserH
#define MyBot_UserH

#include <memory>

#include "MyBot/LanguageCode.h"

namespace MyBot
{
    class User
    {
    public:
        typedef std::shared_ptr<User> Ptr;

        unsigned short RoleId;
        int TotalUsage;
        int UsageLimit;
        std::int64_t UserId;
        LanguageCode LanguageCode;
    };
}

#endif