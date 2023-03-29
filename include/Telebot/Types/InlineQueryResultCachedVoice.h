#ifndef Telebot_InlineQueryResultCachedVoiceH
#define Telebot_InlineQueryResultCachedVoiceH

#include "InlineQueryResult.h"
#include "MessageEntity.h"
#include "InputMessageContent.h"

namespace Telebot
{
    class InlineQueryResultCachedVoice : public InlineQueryResult
    {
    public:
        typedef std::shared_ptr<InlineQueryResultCachedVoice> Ptr;

        static const std::string TYPE;

        InlineQueryResultCachedVoice()
        {
            Type = TYPE;
        }

        std::string VoiceFileId;
        std::string Title;
        std::string Caption;
        std::string ParseMode;
        std::vector<MessageEntity::Ptr> CaptionEntities;
        InputMessageContent::Ptr InputMessageContent;
    };
}

#endif