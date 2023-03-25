#ifndef Telebot_UserSharedH
#define Telebot_UserSharedH

#include <memory>

namespace Telebot
{
    class UserShared
    {
    public:
        typedef std::shared_ptr<UserShared> Ptr;

        int RequestId;
        long long UserId;
    };
}

#endif