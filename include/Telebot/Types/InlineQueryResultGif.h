#ifndef Telebot_InlineQueryResultGifH
#define Telebot_InlineQueryResultGifH

#include "InlineQueryResult.h"
#include "MessageEntity.h"
#include "InputMessageContent.h"

namespace Telebot
{
    class InlineQueryResultGif : public InlineQueryResult
    {
    public:
        typedef std::shared_ptr<InlineQueryResultGif> Ptr;

        static const std::string TYPE;

        InlineQueryResultGif()
        {
            Type = TYPE;
        }

        std::string GifUrl;
        std::int32_t GifWidth;
        std::int32_t GifHeight;
        std::int32_t GifDuration;
        std::string ThumbUrl;
        std::string ThumbMimeType;
        std::string Title;
        std::string Caption;
        std::string ParseMode;
        std::vector<MessageEntity::Ptr> CaptionEntities;
        InputMessageContent::Ptr InputMessageContent;
    };
}

#endif