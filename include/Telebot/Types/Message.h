#ifndef Telebot_MessageH
#define Telebot_MessageH

#include "User.h"
#include "Chat.h"
#include "Message.h"
#include "MessageEntity.h"
#include "Animation.h"
#include "Audio.h"
#include "Document.h"
#include "PhotoSize.h"
#include "Sticker.h"
#include "Video.h"
#include "VideoNote.h"
#include "Voice.h"
#include "Contact.h"
#include "Dice.h"
#include "Game.h"
#include "Poll.h"
#include "Venue.h"
#include "Location.h"
#include "MessageAutoDeleteTimerChanged.h"
#include "Invoice.h"
#include "SuccessfulPayment.h"
#include "UserShared.h"
#include "ChatShared.h"
#include "WriteAccessAllowed.h"
#include "PassportData.h"
#include "ProximityAlertTriggered.h"
#include "ForumTopicCreated.h"
#include "ForumTopicEdited.h"
#include "ForumTopicClosed.h"
#include "ForumTopicReopened.h"
#include "GeneralForumTopicHidden.h"
#include "GeneralForumTopicUnhidden.h"
#include "VideoChatScheduled.h"
#include "VideoChatStarted.h"
#include "VideoChatEnded.h"
#include "VideoChatParticipantsInvited.h"
#include "WebAppData.h"
#include "InlineKeyboardMarkup.h"

namespace Telebot
{
    class Message
    {
    public:
        typedef std::shared_ptr<Message> Ptr;

        std::int32_t message_id;
        std::int32_t message_thread_id;
        User::Ptr from;
        Chat::Ptr sender_chat;
        std::int32_t date;
        Chat::Ptr chat;
        User::Ptr forward_from;
        Chat::Ptr forward_fromChat;
        std::int32_t forward_from_message_id;
        std::string forward_signature;
        std::string forward_sender_name;
        std::int32_t forward_date;
        bool is_topic_message;
        bool is_automatic_forward;
        Message::Ptr reply_to_message;
        User::Ptr via_bot;
        std::int32_t edit_date;
        bool has_protected_content;
        std::string media_group_id;
        std::string author_signature;
        std::string text;
        std::vector<MessageEntity::Ptr> entities;
        Animation::Ptr animation;
        Audio::Ptr audio;
        Document::Ptr document;
        std::vector<PhotoSize::Ptr> photo;
        Sticker::Ptr sticker;
        Video::Ptr video;
        VideoNote::Ptr videoNote;
        Voice::Ptr voice;
        std::string caption;
        std::vector<MessageEntity::Ptr> caption_entities;
        bool has_media_spoiler;
        Contact::Ptr contact;
        Dice::Ptr dice;
        Game::Ptr game;
        Poll::Ptr poll;
        Venue::Ptr venue;
        Location::Ptr location;
        std::vector<User::Ptr> new_chat_members;
        User::Ptr left_chat_member;
        std::string new_chat_title;
        std::vector<PhotoSize::Ptr> new_chat_photo;
        bool delete_chat_photo;
        bool group_chat_created;
        bool supergroup_chat_created;
        bool channel_chat_created;
        MessageAutoDeleteTimerChanged::Ptr message_auto_delete_timer_changed;
        std::int64_t migrate_to_chat_id;
        std::int64_t migrate_from_chat_id;
        Message::Ptr pinned_message;
        Invoice::Ptr invoice;
        SuccessfulPayment::Ptr successful_payment;
        UserShared::Ptr user_shared;
        ChatShared::Ptr chat_shared;
        std::string connected_website;
        WriteAccessAllowed::Ptr write_access_allowed;
        PassportData::Ptr passport_data;
        ProximityAlertTriggered::Ptr proximity_alert_triggered;
        ForumTopicCreated::Ptr forum_topic_created;
        ForumTopicEdited::Ptr forum_topic_edited;
        ForumTopicClosed::Ptr forum_topic_closed;
        ForumTopicReopened::Ptr forum_topic_reopened;
        GeneralForumTopicHidden::Ptr general_forum_topic_hidden;
        GeneralForumTopicUnhidden::Ptr general_forum_topic_unhidden;
        VideoChatScheduled::Ptr video_chat_scheduled;
        VideoChatStarted::Ptr video_chat_started;
        VideoChatEnded::Ptr video_chat_ended;
        VideoChatParticipantsInvited::Ptr video_chat_participants_invited;
        WebAppData::Ptr web_app_data;
        InlineKeyboardMarkup::Ptr reply_markup;
    };

    inline void from_json(const Json& json, Message& object)
    {
        VALUE_FROM_JSON(message_id)
        VALUE_FROM_JSON(message_thread_id)
        OBJECT_FROM_JSON(from)
        OBJECT_FROM_JSON(sender_chat)
        VALUE_FROM_JSON(date)
        OBJECT_FROM_JSON(chat)
        OBJECT_FROM_JSON(forward_from)
        OBJECT_FROM_JSON(forward_fromChat)
        VALUE_FROM_JSON(forward_from_message_id)
        VALUE_FROM_JSON(forward_signature)
        VALUE_FROM_JSON(forward_sender_name)
        VALUE_FROM_JSON(forward_date)
        VALUE_FROM_JSON(is_topic_message)
        VALUE_FROM_JSON(is_automatic_forward)
        OBJECT_FROM_JSON(reply_to_message)
        OBJECT_FROM_JSON(via_bot)
        VALUE_FROM_JSON(edit_date)
        VALUE_FROM_JSON(has_protected_content)
        VALUE_FROM_JSON(media_group_id)
        VALUE_FROM_JSON(author_signature)
        VALUE_FROM_JSON(text)
        OBJECTS_FROM_JSON(entities)
        OBJECT_FROM_JSON(animation)
        OBJECT_FROM_JSON(audio)
        OBJECT_FROM_JSON(document)
        OBJECTS_FROM_JSON(photo)
        OBJECT_FROM_JSON(sticker)
        OBJECT_FROM_JSON(video)
        OBJECT_FROM_JSON(videoNote)
        OBJECT_FROM_JSON(voice)
        VALUE_FROM_JSON(caption)
        OBJECTS_FROM_JSON(caption_entities)
        VALUE_FROM_JSON(has_media_spoiler)
        OBJECT_FROM_JSON(contact)
        OBJECT_FROM_JSON(dice)
        OBJECT_FROM_JSON(game)
        OBJECT_FROM_JSON(poll)
        OBJECT_FROM_JSON(venue)
        OBJECT_FROM_JSON(location)
        OBJECTS_FROM_JSON(new_chat_members)
        OBJECT_FROM_JSON(left_chat_member)
        VALUE_FROM_JSON(new_chat_title)
        OBJECTS_FROM_JSON(new_chat_photo)
        VALUE_FROM_JSON(delete_chat_photo)
        VALUE_FROM_JSON(group_chat_created)
        VALUE_FROM_JSON(supergroup_chat_created)
        VALUE_FROM_JSON(channel_chat_created)
        OBJECT_FROM_JSON(message_auto_delete_timer_changed)
        VALUE_FROM_JSON(migrate_to_chat_id)
        VALUE_FROM_JSON(migrate_from_chat_id)
        OBJECT_FROM_JSON(pinned_message)
        OBJECT_FROM_JSON(invoice)
        OBJECT_FROM_JSON(successful_payment)
        OBJECT_FROM_JSON(user_shared)
        OBJECT_FROM_JSON(chat_shared)
        VALUE_FROM_JSON(connected_website)
        OBJECT_FROM_JSON(write_access_allowed)
        OBJECT_FROM_JSON(passport_data)
        OBJECT_FROM_JSON(proximity_alert_triggered)
        OBJECT_FROM_JSON(forum_topic_created)
        OBJECT_FROM_JSON(forum_topic_edited)
        OBJECT_FROM_JSON(forum_topic_closed)
        OBJECT_FROM_JSON(forum_topic_reopened)
        OBJECT_FROM_JSON(general_forum_topic_hidden)
        OBJECT_FROM_JSON(general_forum_topic_unhidden)
        OBJECT_FROM_JSON(video_chat_scheduled)
        OBJECT_FROM_JSON(video_chat_started)
        OBJECT_FROM_JSON(video_chat_ended)
        OBJECT_FROM_JSON(video_chat_participants_invited)
        OBJECT_FROM_JSON(web_app_data)
        OBJECT_FROM_JSON(reply_markup)
    }
}

#endif