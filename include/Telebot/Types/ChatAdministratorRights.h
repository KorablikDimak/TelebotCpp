#ifndef Telebot_ChatAdministratorRightsH
#define Telebot_ChatAdministratorRightsH

#include "Common/JsonMacros.h"

namespace Telebot
{
    class ChatAdministratorRights
    {
    public:
        typedef std::shared_ptr<ChatAdministratorRights> Ptr;

        bool is_anonymous;
        bool can_manage_chat;
        bool can_delete_messages;
        bool can_manage_videoChats;
        bool can_restrict_members;
        bool can_promote_members;
        bool can_change_info;
        bool can_invite_users;
        bool can_post_messages;
        bool can_edit_messages;
        bool can_pin_messages;
        bool can_manage_topics;
    };

    inline void to_json(Json& json, const ChatAdministratorRights::Ptr& object)
    {
        VALUE_TO_JSON(is_anonymous)
        VALUE_TO_JSON(can_manage_chat)
        VALUE_TO_JSON(can_delete_messages)
        VALUE_TO_JSON(can_manage_videoChats)
        VALUE_TO_JSON(can_restrict_members)
        VALUE_TO_JSON(can_promote_members)
        VALUE_TO_JSON(can_change_info)
        VALUE_TO_JSON(can_invite_users)
        VALUE_TO_JSON(can_post_messages)
        VALUE_TO_JSON(can_edit_messages)
        VALUE_TO_JSON(can_pin_messages)
        VALUE_TO_JSON(can_manage_topics)
    }
}

#endif