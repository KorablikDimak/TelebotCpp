#ifndef Telebot_InlineQueryResultCachedPhotoH
#define Telebot_InlineQueryResultCachedPhotoH

#include "InlineQueryResult.h"
#include "MessageEntity.h"
#include "InputMessageContent.h"

namespace Telebot
{
    class InlineQueryResultCachedPhoto : public InlineQueryResult
    {
    public:
        typedef std::shared_ptr<InlineQueryResultCachedPhoto> Ptr;

        static const std::string TYPE;

        InlineQueryResultCachedPhoto()
        {
            Type = TYPE;
        }

        std::string PhotoFileId;
        std::string Title;
        std::string Description;
        std::string Caption;
        std::string ParseMode;
        std::vector<MessageEntity::Ptr> CaptionEntities;
        InputMessageContent::Ptr InputMessageContent;
    };
}

#endif