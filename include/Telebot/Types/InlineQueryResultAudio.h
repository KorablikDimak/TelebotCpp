#ifndef Telebot_InlineQueryResultAudioH
#define Telebot_InlineQueryResultAudioH

#include "InlineQueryResult.h"
#include "MessageEntity.h"
#include "InputMessageContent.h"

namespace Telebot
{
    class InlineQueryResultAudio : public InlineQueryResult
    {
    public:
        typedef std::shared_ptr<InlineQueryResultAudio> Ptr;

        static const std::string TYPE;

        InlineQueryResultAudio()
        {
            Type = TYPE;
        }

        std::string AudioUrl;
        std::string Title;
        std::string Caption;
        std::string ParseMode;
        std::vector<MessageEntity::Ptr> CaptionEntities;
        std::string Performer;
        std::int32_t AudioDuration;
        InputMessageContent::Ptr InputMessageContent;
    };
}

#endif