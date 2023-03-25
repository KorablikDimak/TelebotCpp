#ifndef Telebot_ChatH
#define Telebot_ChatH

#include "Telebot/Types/ChatPhoto.h"
#include "Telebot/Types/ChatPermissions.h"
#include "Telebot/Types/ChatLocation.h"

namespace Telebot
{
    class Message;

    class Chat
    {
    public:
        typedef std::shared_ptr<Chat> Ptr;

        enum class Type
        {
            Private, Group, Supergroup, Channel
        };

        long long Id;
        Type Type;
        std::string Title;
        std::string Username;
        std::string FirstName;
        std::string LastName;
        bool IsForum;
        ChatPhoto::Ptr Photo;
        std::vector<std::string> ActiveUsernames;
        std::string EmojiStatusCustomEmojiId;
        std::string Bio;
        bool HasPrivateForwards;
        bool HasRestrictedVoiceAndVideoMessages;
        bool JoinToSendMessages;
        bool JoinByRequest;
        std::string Description;
        std::string InviteLink;
        std::shared_ptr<Message> PinnedMessage;
        ChatPermissions::Ptr Permissions;
        int SlowModeDelay;
        int MessageAutoDeleteTime;
        bool HasAggressiveAntiSpamEnabled;
        bool HasHiddenMembers;
        bool HasProtectedContent;
        std::string StickerSetName;
        bool CanSetStickerSet;
        long long LinkedChatId;
        ChatLocation::Ptr Location;
    };
}

#endif