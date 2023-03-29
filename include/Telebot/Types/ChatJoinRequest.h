#ifndef Telebot_ChatJoinRequestH
#define Telebot_ChatJoinRequestH

#include "Chat.h"
#include "User.h"
#include "ChatInviteLink.h"

namespace Telebot
{
    class ChatJoinRequest
    {
    public:
        typedef std::shared_ptr<ChatJoinRequest> Ptr;

        Chat::Ptr Chat;
        User::Ptr From;
        std::int64_t UserChatId;
        std::int32_t Date;
        std::string Bio;
        ChatInviteLink::Ptr InviteLink;
    };
}

#endif