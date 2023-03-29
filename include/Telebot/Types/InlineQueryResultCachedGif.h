#ifndef Telebot_InlineQueryResultCachedGifH
#define Telebot_InlineQueryResultCachedGifH

#include "InlineQueryResult.h"
#include "MessageEntity.h"
#include "InputMessageContent.h"

namespace Telebot
{
    class InlineQueryResultCachedGif : public InlineQueryResult
    {
    public:
        typedef std::shared_ptr<InlineQueryResultCachedGif> Ptr;

        static const std::string TYPE;

        InlineQueryResultCachedGif()
        {
            Type = TYPE;
        }

        std::string GifFileId;
        std::string Title;
        std::string Caption;
        std::string ParseMode;
        std::vector<MessageEntity::Ptr> CaptionEntities;
        InputMessageContent::Ptr InputMessageContent;
    };
}

#endif