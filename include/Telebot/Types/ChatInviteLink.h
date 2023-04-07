#ifndef Telebot_ChatInviteLinkH
#define Telebot_ChatInviteLinkH

#include "User.h"

namespace Telebot
{
class ChatInviteLink
{
    public:
        typedef std::shared_ptr<ChatInviteLink> Ptr;

        std::string invite_link;
        User::Ptr creator;
        bool creates_join_request;
        bool is_primary;
        bool is_revoked;
        std::string name;
        std::uint32_t expire_date;
        std::uint32_t member_limit;
        std::uint32_t pending_join_request_count;
    };

    inline void from_json(const Json& json, ChatInviteLink& object)
    {
        VALUE_FROM_JSON(invite_link)
        OBJECT_FROM_JSON(creator)
        VALUE_FROM_JSON(creates_join_request)
        VALUE_FROM_JSON(is_primary)
        VALUE_FROM_JSON(is_revoked)
        VALUE_FROM_JSON(name)
        VALUE_FROM_JSON(expire_date)
        VALUE_FROM_JSON(member_limit)
        VALUE_FROM_JSON(pending_join_request_count)
    }
}

#endif