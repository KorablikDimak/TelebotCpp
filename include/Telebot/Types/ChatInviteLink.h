#ifndef Telebot_ChatInviteLinkH
#define Telebot_ChatInviteLinkH

#include "User.h"

namespace Telebot
{
class ChatInviteLink
{
    public:
        typedef std::shared_ptr<ChatInviteLink> Ptr;

        std::string InviteLink;
        User::Ptr Creator;
        bool CreatesJoinRequest;
        bool IsPrimary;
        bool IsRevoked;
        std::string Name;
        std::uint32_t ExpireDate;
        std::uint32_t MemberLimit;
        std::uint32_t PendingJoinRequestCount;
    };
}

#endif