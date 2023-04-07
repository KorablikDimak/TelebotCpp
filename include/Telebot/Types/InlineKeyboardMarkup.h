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

        std::vector<std::vector<InlineKeyboardButton::Ptr>> inline_keyboard;
    };

    inline void from_json(const Json& json, InlineKeyboardMarkup& object)
    {
        if (json.contains("inline_keyboard"))
            for (const Json& element : json.at("inline_keyboard"))
            {
                std::vector<InlineKeyboardButton::Ptr> innerVector;
                for (const Json& innerElement : element)
                {
                    InlineKeyboardButton::Ptr button = std::make_shared<InlineKeyboardButton>();
                    *button = innerElement.get<InlineKeyboardButton>();
                    innerVector.push_back(button);
                }
                object.inline_keyboard.push_back(innerVector);
            }
    }
}

#endif