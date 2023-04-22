#ifndef Telebot_DiceH
#define Telebot_DiceH

#include "Common/JsonMacros.h"

namespace Telebot
{
    class Dice
    {
    public:
        typedef std::shared_ptr<Dice> Ptr;

        std::string emoji;
        std::int32_t value;
    };

    inline void from_json(const Json& json, Dice& object)
    {
        VALUE_FROM_JSON(emoji)
        VALUE_FROM_JSON(value)
    }
}

#endif