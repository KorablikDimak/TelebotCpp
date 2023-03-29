#ifndef Telebot_InlineQueryResultCachedAudioH
#define Telebot_InlineQueryResultCachedAudioH

#include <vector>

#include "InlineQueryResult.h"
#include "MessageEntity.h"
#include "InputMessageContent.h"

namespace Telebot
{
    class InlineQueryResultCachedAudio : public InlineQueryResult
    {
    public:
        typedef std::shared_ptr<InlineQueryResultCachedAudio> Ptr;

        static const std::string TYPE;

        InlineQueryResultCachedAudio()
        {
            Type = TYPE;
        }

        std::string AudioFileId;
        std::string Caption;
        std::string ParseMode;
        std::vector<MessageEntity::Ptr> CaptionEntities;
        InputMessageContent::Ptr InputMessageContent;
    };
}

#endif