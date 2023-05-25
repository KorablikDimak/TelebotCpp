#ifndef Telebot_KeyboardButtonRequestChatH
#define Telebot_KeyboardButtonRequestChatH

#include "ChatAdministratorRights.h"

namespace Telebot
{
    class KeyboardButtonRequestChat
    {
    public:
        typedef std::shared_ptr<KeyboardButtonRequestChat> Ptr;

        std::int32_t request_id;
        bool chat_is_channel;
        bool chat_is_forum;
        bool chat_has_username;
        bool chat_is_created;
        ChatAdministratorRights::Ptr user_administrator_rights;
        bool bot_is_member;
    };

    inline void to_json(Json& json, const KeyboardButtonRequestChat::Ptr& object)
    {
        VALUE_TO_JSON(request_id)
        VALUE_TO_JSON(chat_is_channel)
        VALUE_TO_JSON(chat_is_forum)
        VALUE_TO_JSON(chat_has_username)
        VALUE_TO_JSON(chat_is_created)
        OBJECT_TO_JSON(user_administrator_rights)
        VALUE_TO_JSON(bot_is_member)
    }
}

#endif