#ifndef Telebot_InlineQueryResultVoiceH
#define Telebot_InlineQueryResultVoiceH

#include "InlineQueryResult.h"
#include "MessageEntity.h"
#include "InputMessageContent.h"

namespace Telebot
{
    class InlineQueryResultVoice : public InlineQueryResult
    {
    public:
        typedef std::shared_ptr<InlineQueryResultVoice> Ptr;

        static const std::string TYPE;

        InlineQueryResultVoice()
        {
            Type = TYPE;
        };

        std::string VoiceUrl;
        std::string Title;
        std::string Caption;
        std::string parseMode;
        std::vector<MessageEntity::Ptr> CaptionEntities;
        std::int32_t VoiceDuration;
        InputMessageContent::Ptr InputMessageContent;
    };
}

#endif