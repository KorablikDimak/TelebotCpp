#ifndef Telebot_ChatInviteLinkH
#define Telebot_ChatInviteLinkH

#include "Telebot/Types/User.h"

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
        unsigned int ExpireDate;
        unsigned int MemberLimit;
        unsigned int PendingJoinRequestCount;
    };
}

#endif