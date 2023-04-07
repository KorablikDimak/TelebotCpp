#ifndef Telebot_ChatPermissionsH
#define Telebot_ChatPermissionsH

#include "Telebot/JsonMacros.h"

namespace Telebot
{
    class ChatPermissions
    {
    public:
        typedef std::shared_ptr<ChatPermissions> Ptr;

        bool can_send_messages;
        bool can_send_audios;
        bool can_send_documents;
        bool can_send_photos;
        bool can_send_videos;
        bool can_send_video_notes;
        bool can_send_voice_notes;
        bool can_send_polls;
        bool can_send_other_messages;
        bool can_add_web_page_previews;
        bool can_change_info;
        bool can_invite_users;
        bool can_pin_messages;
        bool can_manage_topics;
    };

    inline void from_json(const Json& json, ChatPermissions& object)
    {
        VALUE_FROM_JSON(can_send_messages)
        VALUE_FROM_JSON(can_send_audios)
        VALUE_FROM_JSON(can_send_documents)
        VALUE_FROM_JSON(can_send_photos)
        VALUE_FROM_JSON(can_send_videos)
        VALUE_FROM_JSON(can_send_video_notes)
        VALUE_FROM_JSON(can_send_voice_notes)
        VALUE_FROM_JSON(can_send_polls)
        VALUE_FROM_JSON(can_send_other_messages)
        VALUE_FROM_JSON(can_add_web_page_previews)
        VALUE_FROM_JSON(can_change_info)
        VALUE_FROM_JSON(can_invite_users)
        VALUE_FROM_JSON(can_pin_messages)
        VALUE_FROM_JSON(can_manage_topics)
    }
}

#endif