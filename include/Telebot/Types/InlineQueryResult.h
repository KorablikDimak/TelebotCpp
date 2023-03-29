#ifndef Telebot_InlineQueryResultH
#define Telebot_InlineQueryResultH

#include "InlineKeyboardMarkup.h"

namespace Telebot
{
    class InlineQueryResult
    {
    public:
        typedef std::shared_ptr<InlineQueryResult> Ptr;

        InlineQueryResult() = default;
        virtual ~InlineQueryResult() = default;

        std::string Type;
        std::string Id;
        InlineKeyboardMarkup::Ptr ReplyMarkup;
    };
}

#endif