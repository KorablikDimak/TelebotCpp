#ifndef Telebot_InlineQueryResultCachedDocumentH
#define Telebot_InlineQueryResultCachedDocumentH

#include "InlineQueryResult.h"
#include "MessageEntity.h"
#include "InputMessageContent.h"

namespace Telebot
{
    class InlineQueryResultCachedDocument : public InlineQueryResult
    {
    public:
        typedef std::shared_ptr<InlineQueryResultCachedDocument> Ptr;

        static const std::string TYPE;

        InlineQueryResultCachedDocument()
        {
            Type = TYPE;
        }

        std::string Title;
        std::string DocumentFileId;
        std::string Description;
        std::string Caption;
        std::string ParseMode;
        std::vector<MessageEntity::Ptr> CaptionEntities;
        InputMessageContent::Ptr InputMessageContent;
    };
}

#endif