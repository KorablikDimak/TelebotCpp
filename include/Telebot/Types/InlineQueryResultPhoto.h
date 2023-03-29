#ifndef Telebot_InlineQueryResultPhotoH
#define Telebot_InlineQueryResultPhotoH

#include "InlineQueryResult.h"
#include "MessageEntity.h"
#include "InputMessageContent.h"

namespace Telebot
{
    class InlineQueryResultPhoto : public InlineQueryResult
    {
    public:
        typedef std::shared_ptr<InlineQueryResultPhoto> Ptr;

        static const std::string TYPE;

        InlineQueryResultPhoto()
        {
            Type = TYPE;
        }

        std::string PhotoUrl;
        std::string ThumbUrl;
        std::int32_t PhotoWidth;
        std::int32_t PhotoHeight;
        std::string Title;
        std::string Description;
        std::string Caption;
        std::string ParseMode;
        std::vector<MessageEntity::Ptr> CaptionEntities;
        InputMessageContent::Ptr InputMessageContent;
    };
}

#endif