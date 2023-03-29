#ifndef Telebot_ReplyKeyboardMarkupH
#define Telebot_ReplyKeyboardMarkupH

#include <vector>

#include "GenericReply.h"
#include "KeyboardButton.h"

namespace Telebot
{
    class ReplyKeyboardMarkup : public GenericReply
    {
    public:
        typedef std::shared_ptr<ReplyKeyboardMarkup> Ptr;

        std::vector<std::vector<KeyboardButton::Ptr>> Keyboard;
        bool IsPersistent;
        bool ResizeKeyboard;
        bool OneTimeKeyboard;
        std::string InputFieldPlaceholder;
        bool Selective;
    };
}

#endif