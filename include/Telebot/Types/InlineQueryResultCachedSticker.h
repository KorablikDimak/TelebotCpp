#ifndef Telebot_InlineQueryResultCachedStickerH
#define Telebot_InlineQueryResultCachedStickerH

#include "InlineQueryResult.h"
#include "InputMessageContent.h"

namespace Telebot
{
    class InlineQueryResultCachedSticker : public InlineQueryResult
    {
    public:
        typedef std::shared_ptr<InlineQueryResultCachedSticker> Ptr;

        static const std::string TYPE;

        InlineQueryResultCachedSticker()
        {
            Type = TYPE;
        }

        std::string StickerFileId;
        InputMessageContent::Ptr InputMessageContent;
    };
}

#endif