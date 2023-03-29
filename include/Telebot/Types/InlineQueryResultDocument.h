#ifndef Telebot_InlineQueryResultDocumentH
#define Telebot_InlineQueryResultDocumentH

#include "InlineQueryResult.h"
#include "MessageEntity.h"
#include "InputMessageContent.h"

namespace Telebot
{
    class InlineQueryResultDocument : public InlineQueryResult
    {
    public:
        typedef std::shared_ptr<InlineQueryResultDocument> Ptr;

        static const std::string TYPE;

        InlineQueryResultDocument()
        {
            Type = TYPE;
        }

        std::string Title;
        std::string Caption;
        std::string ParseMode;
        std::vector<MessageEntity::Ptr> CaptionEntities;
        std::string DocumentUrl;
        std::string MimeType;
        std::string Description;
        InputMessageContent::Ptr InputMessageContent;
        std::string ThumbUrl;
        std::int32_t ThumbWidth;
        std::int32_t ThumbHeight;
    };
}

#endif