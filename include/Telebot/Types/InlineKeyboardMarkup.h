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

        ~InlineKeyboardMarkup() override = default;

        std::vector<std::vector<InlineKeyboardButton::Ptr>> inline_keyboard;

        void SetButton(const InlineKeyboardButton::Ptr& button, unsigned char row, unsigned char column);
        void RemoveButton(unsigned char row, unsigned char column);

        void ToJson(Json& json, const GenericReply::Ptr& object) override;
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

    inline void to_json(Json& json, const InlineKeyboardMarkup::Ptr& object)
    {
        json["inline_keyboard"] = object->inline_keyboard;
    }
}

#endif