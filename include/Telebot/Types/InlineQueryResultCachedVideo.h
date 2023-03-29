#ifndef Telebot_InlineQueryResultCachedVideoH
#define Telebot_InlineQueryResultCachedVideoH

#include "InlineQueryResult.h"
#include "MessageEntity.h"
#include "InputMessageContent.h"

namespace Telebot
{
    class InlineQueryResultCachedVideo : public InlineQueryResult
    {
    public:
        typedef std::shared_ptr<InlineQueryResultCachedVideo> Ptr;

        static const std::string TYPE;

        InlineQueryResultCachedVideo()
        {
            Type = TYPE;
        }

        std::string VideoFileId;
        std::string Title;
        std::string Description;
        std::string Caption;
        std::string ParseMode;
        std::vector<MessageEntity::Ptr> CaptionEntities;
        InputMessageContent::Ptr InputMessageContent;
    };
}

#endif