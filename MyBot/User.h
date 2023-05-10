#ifndef MyBot_UserH
#define MyBot_UserH

#include <memory>

namespace MyBot
{
    class User
    {
    public:
        typedef std::shared_ptr<User> Ptr;

        std::int64_t UserId;
        unsigned short RoleId;
        unsigned short ContextLimit;
        int TotalUsage;
        int UsageLimit;
    };
}

#endif