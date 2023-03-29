#ifndef Telebot_InlineKeyboardMarkupH
#define Telebot_InlineKeyboardMarkupH

#include "GenericReply.h"
#include "InlineKeyboardButton.h"

namespace Telebot
{
    class InlineKeyboardMarkup : public GenericReply
    {
    public:
        typedef std::shared_ptr<InlineKeyboardMarkup> Ptr;

        std::vector<std::vector<InlineKeyboardButton::Ptr>> InlineKeyboard;
    };
}

#endif