#ifndef Telebot_MessageH
#define Telebot_MessageH

#include "Telebot/Types/User.h"
#include "Telebot/Types/Chat.h"
#include "Telebot/Types/Message.h"
#include "Telebot/Types/MessageEntity.h"
#include "Telebot/Types/Animation.h"
#include "Telebot/Types/Audio.h"
#include "Telebot/Types/Document.h"
#include "Telebot/Types/PhotoSize.h"
#include "Telebot/Types/Sticker.h"
#include "Telebot/Types/Video.h"
#include "Telebot/Types/VideoNote.h"
#include "Telebot/Types/Voice.h"
#include "Telebot/Types/Contact.h"
#include "Telebot/Types/Dice.h"
#include "Telebot/Types/Game.h"
#include "Telebot/Types/Poll.h"
#include "Telebot/Types/Venue.h"
#include "Telebot/Types/Location.h"
#include "Telebot/Types/MessageAutoDeleteTimerChanged.h"
#include "Telebot/Types/Invoice.h"
#include "Telebot/Types/SuccessfulPayment.h"
#include "Telebot/Types/UserShared.h"
#include "Telebot/Types/ChatShared.h"
#include "Telebot/Types/WriteAccessAllowed.h"
#include "Telebot/Types/PassportData.h"
#include "Telebot/Types/ProximityAlertTriggered.h"
#include "Telebot/Types/ForumTopicCreated.h"
#include "Telebot/Types/ForumTopicEdited.h"
#include "Telebot/Types/ForumTopicClosed.h"
#include "Telebot/Types/ForumTopicReopened.h"
#include "Telebot/Types/GeneralForumTopicHidden.h"
#include "Telebot/Types/GeneralForumTopicUnhidden.h"
#include "Telebot/Types/VideoChatScheduled.h"
#include "Telebot/Types/VideoChatStarted.h"
#include "Telebot/Types/VideoChatEnded.h"
#include "Telebot/Types/VideoChatParticipantsInvited.h"
#include "Telebot/Types/WebAppData.h"
#include "Telebot/Types/InlineKeyboardMarkup.h"

namespace Telebot
{
    class Message
    {
    public:
        typedef std::shared_ptr<Message> Ptr;

        int MessageId;
        int MessageThreadId;
        User::Ptr From;
        Chat::Ptr SenderChat;
        int Ddate;
        Chat::Ptr Chat;
        User::Ptr ForwardFrom;
        Chat::Ptr ForwardFromChat;
        int ForwardFromMessageId;
        std::string ForwardSignature;
        std::string ForwardSenderName;
        int ForwardDate;
        bool IsTopicMessage;
        bool IsAutomaticForward;
        Message::Ptr ReplyToMessage;
        User::Ptr ViaBot;
        int EditDate;
        bool HasProtectedContent;
        std::string MediaGroupId;
        std::string AuthorSignature;
        std::string Text;
        std::vector<MessageEntity::Ptr> Entities;
        Animation::Ptr Animation;
        Audio::Ptr Audio;
        Document::Ptr Document;
        std::vector<PhotoSize::Ptr> Photo;
        Sticker::Ptr Sticker;
        Video::Ptr Video;
        VideoNote::Ptr VideoNote;
        Voice::Ptr Voice;
        std::string Caption;
        std::vector<MessageEntity::Ptr> CaptionEntities;
        bool HasMediaSpoiler;
        Contact::Ptr Contact;
        Dice::Ptr Dice;
        Game::Ptr Game;
        Poll::Ptr Poll;
        Venue::Ptr Venue;
        Location::Ptr Location;
        std::vector<User::Ptr> NewChatMembers;
        User::Ptr LeftChatMember;
        std::string NewChatTitle;
        std::vector<PhotoSize::Ptr> NewChatPhoto;
        bool DeleteChatPhoto;
        bool GroupChatCreated;
        bool SupergroupChatCreated;
        bool ChannelChatCreated;
        MessageAutoDeleteTimerChanged::Ptr MessageAutoDeleteTimerChanged;
        long long MigrateToChatId;
        long long MigrateFromChatId;
        Message::Ptr PinnedMessage;
        Invoice::Ptr Invoice;
        SuccessfulPayment::Ptr SuccessfulPayment;
        UserShared::Ptr UserShared;
        ChatShared::Ptr ChatShared;
        std::string ConnectedWebsite;
        WriteAccessAllowed::Ptr WriteAccessAllowed;
        PassportData::Ptr PassportData;
        ProximityAlertTriggered::Ptr ProximityAlertTriggered;
        ForumTopicCreated::Ptr ForumTopicCreated;
        ForumTopicEdited::Ptr ForumTopicEdited;
        ForumTopicClosed::Ptr ForumTopicClosed;
        ForumTopicReopened::Ptr ForumTopicReopened;
        GeneralForumTopicHidden::Ptr GeneralForumTopicHidden;
        GeneralForumTopicUnhidden::Ptr GeneralForumTopicUnhidden;
        VideoChatScheduled::Ptr VideoChatScheduled;
        VideoChatStarted::Ptr VideoChatStarted;
        VideoChatEnded::Ptr VideoChatEnded;
        VideoChatParticipantsInvited::Ptr VideoChatParticipantsInvited;
        WebAppData::Ptr WebAppData;
        InlineKeyboardMarkup::Ptr ReplyMarkup;
    };
}

#endif