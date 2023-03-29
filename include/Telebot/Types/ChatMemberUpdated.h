#ifndef Telebot_ChatMemberUpdatedH
#define Telebot_ChatMemberUpdatedH

#include "Chat.h"
#include "User.h"
#include "ChatMember.h"
#include "ChatInviteLink.h"

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