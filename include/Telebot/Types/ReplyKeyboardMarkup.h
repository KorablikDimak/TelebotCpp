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

        ~ReplyKeyboardMarkup() override = default;

        std::vector<std::vector<KeyboardButton::Ptr>> keyboard;
        bool is_persistent;
        bool resize_keyboard;
        bool one_time_keyboard;
        std::string input_field_placeholder;
        bool selective;

        void ToJson(Json& json, const GenericReply::Ptr& object) override;
    };

    inline void to_json(Json& json, const ReplyKeyboardMarkup::Ptr& object)
    {
        json["keyboard"] = object->keyboard;
        VALUE_TO_JSON(is_persistent)
        VALUE_TO_JSON(resize_keyboard)
        VALUE_TO_JSON(one_time_keyboard)
        if (!object->input_field_placeholder.empty()) VALUE_TO_JSON(input_field_placeholder)
        VALUE_TO_JSON(selective)
    }
}

#endif