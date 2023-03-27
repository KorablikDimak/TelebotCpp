#ifndef Telebot_UserSharedH
#define Telebot_UserSharedH

#include <memory>

namespace Telebot
{
    class UserShared
    {
    public:
        typedef std::shared_ptr<UserShared> Ptr;

        std::int32_t RequestId;
        std::int64_t UserId;
    };
}

#endif