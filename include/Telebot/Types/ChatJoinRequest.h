#ifndef Telebot_ChatJoinRequestH
#define Telebot_ChatJoinRequestH

#include "Chat.h"
#include "ChatInviteLink.h"

namespace Telebot
{
    class ChatJoinRequest
    {
    public:
        typedef std::shared_ptr<ChatJoinRequest> Ptr;

        Chat::Ptr chat;
        User::Ptr from;
        std::int64_t user_chat_id;
        std::int32_t date;
        std::string bio;
        ChatInviteLink::Ptr invite_link;
    };

    inline void from_json(const Json& json, ChatJoinRequest& object)
    {
        OBJECT_FROM_JSON(chat)
        OBJECT_FROM_JSON(from)
        VALUE_FROM_JSON(user_chat_id)
        VALUE_FROM_JSON(date)
        VALUE_FROM_JSON(bio)
        OBJECT_FROM_JSON(invite_link)
    }
}

#endif