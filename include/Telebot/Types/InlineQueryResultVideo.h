#ifndef Telebot_InlineQueryResultVideoH
#define Telebot_InlineQueryResultVideoH

#include "InlineQueryResult.h"
#include "MessageEntity.h"
#include "InputMessageContent.h"

namespace Telebot
{
    class InlineQueryResultVideo : public InlineQueryResult
    {
    public:
        typedef std::shared_ptr<InlineQueryResultVideo> Ptr;

        static const std::string TYPE;

        InlineQueryResultVideo()
        {
            Type = TYPE;
        };

        std::string VideoUrl;
        std::string MimeType;
        std::string ThumbUrl;
        std::string Title;
        std::string Caption;
        std::string ParseMode;
        std::vector<MessageEntity::Ptr> CaptionEntities;
        std::int32_t VideoWidth;
        std::int32_t VideoHeight;
        std::int32_t VideoDuration;
        std::string Description;
        InputMessageContent::Ptr InputMessageContent;
    };
}

#endif