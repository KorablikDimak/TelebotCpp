#ifndef Telebot_ReplyKeyboardRemoveH
#define Telebot_ReplyKeyboardRemoveH

#include "GenericReply.h"

namespace Telebot
{
    class ReplyKeyboardRemove : public GenericReply
    {
    public:
        typedef std::shared_ptr<ReplyKeyboardRemove> Ptr;

        ~ReplyKeyboardRemove() override = default;

        bool remove_keyboard;
        bool selective;

        void ToJson(Json& json, const GenericReply::Ptr& object) override;
    };

    inline void to_json(Json& json, const ReplyKeyboardRemove::Ptr& object)
    {
        VALUE_TO_JSON(remove_keyboard)
        VALUE_TO_JSON(selective)
    }
}

#endif