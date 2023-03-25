#ifndef Telebot_ChatSharedH
#define Telebot_ChatSharedH

#include <memory>

namespace Telebot
{
    class ChatShared
    {
    public:
        typedef std::shared_ptr<ChatShared> Ptr;

        int RequestId;
        long long UserId;
    };
}

#endif