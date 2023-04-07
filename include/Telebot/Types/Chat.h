#ifndef Telebot_ChatH
#define Telebot_ChatH

#include "ChatPhoto.h"
#include "ChatPermissions.h"
#include "ChatLocation.h"

namespace Telebot
{
    class Message;

    class Chat
    {
    public:
        typedef std::shared_ptr<Chat> Ptr;

        enum class Type
        {
            Private, group, supergroup, channel
        };

        std::int64_t id;
        std::string type;
        std::string title;
        std::string username;
        std::string first_name;
        std::string last_name;
        bool is_forum;
        ChatPhoto::Ptr photo;
        std::vector<std::string> active_usernames;
        std::string emoji_status_custom_emoji_id;
        std::string bio;
        bool has_private_forwards;
        bool has_restricted_voice_and_video_messages;
        bool join_to_send_messages;
        bool join_by_request;
        std::string description;
        std::string invite_link;
        std::shared_ptr<Message> pinned_message;
        ChatPermissions::Ptr permissions;
        std::int32_t slow_mode_delay;
        std::int32_t message_auto_delete_time;
        bool has_aggressive_anti_spam_enabled;
        bool has_hidden_members;
        bool has_protected_content;
        std::string sticker_set_name;
        bool can_set_sticker_set;
        std::int64_t linked_chat_id;
        ChatLocation::Ptr location;
    };

    inline void from_json(const Json& json, Chat& object)
    {
        VALUE_FROM_JSON(id)
        VALUE_FROM_JSON(type)
        VALUE_FROM_JSON(title)
        VALUE_FROM_JSON(username)
        VALUE_FROM_JSON(first_name)
        VALUE_FROM_JSON(last_name)
        VALUE_FROM_JSON(is_forum)
        OBJECT_FROM_JSON(photo)
        VALUES_FROM_JSON(active_usernames)
        VALUE_FROM_JSON(emoji_status_custom_emoji_id)
        VALUE_FROM_JSON(bio)
        VALUE_FROM_JSON(has_private_forwards)
        VALUE_FROM_JSON(has_restricted_voice_and_video_messages)
        VALUE_FROM_JSON(join_to_send_messages)
        VALUE_FROM_JSON(join_by_request)
        VALUE_FROM_JSON(description)
        VALUE_FROM_JSON(invite_link)
        //OBJECT_FROM_JSON(pinned_message)
        OBJECT_FROM_JSON(permissions)
        VALUE_FROM_JSON(slow_mode_delay)
        VALUE_FROM_JSON(message_auto_delete_time)
        VALUE_FROM_JSON(has_aggressive_anti_spam_enabled)
        VALUE_FROM_JSON(has_hidden_members)
        VALUE_FROM_JSON(has_protected_content)
        VALUE_FROM_JSON(sticker_set_name)
        VALUE_FROM_JSON(can_set_sticker_set)
        VALUE_FROM_JSON(linked_chat_id)
        OBJECT_FROM_JSON(location)
    }
}

#endif