#ifndef Telebot_MessageEntityH
#define Telebot_MessageEntityH

#include "Telebot/Types/User.h"

namespace Telebot
{
    class MessageEntity
    {
    public:
        typedef std::shared_ptr<MessageEntity> Ptr;

        enum class Type
        {
            Mention, Hashtag, Cashtag, BotCommand, Url, Email, PhoneNumber, Bold, Italic, Underline, Strikethrough,
            Spoiler, Code, Pre, TextLink, TextMention, CustomEmoji
        };

        Type Type;
        int Offset;
        int Length;
        std::string Url;
        User::Ptr User;
        std::string Language;
        std::string CustomEmojiId;
    };
}

#endif