#ifndef Telebot_ChatSharedH
#define Telebot_ChatSharedH

#include <memory>

namespace Telebot
{
    class ChatShared
    {
    public:
        typedef std::shared_ptr<ChatShared> Ptr;

        std::int32_t RequestId;
        std::int64_t UserId;
    };
}

#endif