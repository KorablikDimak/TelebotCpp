#ifndef Telebot_ChatJoinRequestH
#define Telebot_ChatJoinRequestH

#include "Telebot/Types/Chat.h"
#include "Telebot/Types/User.h"
#include "Telebot/Types/ChatInviteLink.h"

namespace Telebot
{
    class ChatJoinRequest
    {
    public:
        typedef std::shared_ptr<ChatJoinRequest> Ptr;

        Chat::Ptr Chat;
        User::Ptr From;
        long long UserChatId;
        int Date;
        std::string Bio;
        ChatInviteLink::Ptr InviteLink;
    };
}

#endif