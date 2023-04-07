#ifndef Telebot_MessageEntityH
#define Telebot_MessageEntityH

#include "User.h"

namespace Telebot
{
    class MessageEntity
    {
    public:
        typedef std::shared_ptr<MessageEntity> Ptr;

        enum class Type
        {
            mention, hashtag, cashtag, bot_command, url, email, phone_number, bold, italic, underline, strikethrough,
            spoiler, code, pre, text_link, text_mention, custom_emoji
        };

        std::string type;
        std::int32_t offset;
        std::int32_t length;
        std::string url;
        User::Ptr user;
        std::string language;
        std::string customEmojiId;
    };

    inline void from_json(const Json& json, MessageEntity& object)
    {
        VALUE_FROM_JSON(type)
        VALUE_FROM_JSON(offset)
        VALUE_FROM_JSON(length)
        VALUE_FROM_JSON(url)
        OBJECT_FROM_JSON(user)
        VALUE_FROM_JSON(language)
        VALUE_FROM_JSON(customEmojiId)
    }
}

#endif