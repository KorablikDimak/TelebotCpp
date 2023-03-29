#ifndef Telebot_InlineQueryResultCachedMpeg4GifH
#define Telebot_InlineQueryResultCachedMpeg4GifH

#include "InlineQueryResult.h"
#include "MessageEntity.h"
#include "InputMessageContent.h"

namespace Telebot
{
    class InlineQueryResultCachedMpeg4Gif : public InlineQueryResult
    {
    public:
        typedef std::shared_ptr<InlineQueryResultCachedMpeg4Gif> Ptr;

        static const std::string TYPE;

        InlineQueryResultCachedMpeg4Gif()
        {
            Type = TYPE;
        }

        std::string Mpeg4FileId;
        std::string Title;
        std::string Caption;
        std::string ParseMode;
        std::vector<MessageEntity::Ptr> CaptionEntities;
        InputMessageContent::Ptr InputMessageContent;
    };
}

#endif