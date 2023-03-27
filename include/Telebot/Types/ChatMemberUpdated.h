#ifndef Telebot_ChatMemberUpdatedH
#define Telebot_ChatMemberUpdatedH

#include "Telebot/Types/Chat.h"
#include "Telebot/Types/User.h"
#include "Telebot/Types/ChatMember.h"
#include "Telebot/Types/ChatInviteLink.h"

namespace Telebot
{
    class ChatMemberUpdated
    {
    public:
        typedef std::shared_ptr<ChatMemberUpdated> Ptr;

        Chat::Ptr Chat;
        User::Ptr From;
        std::uint32_t Date;
        ChatMember::Ptr OldChatMember;
        ChatMember::Ptr NewChatMember;
        ChatInviteLink::Ptr InviteLink;
    };
}

#endif