#ifndef Telebot_DiceH
#define Telebot_DiceH

#include <memory>

namespace Telebot
{
    class Dice
    {
    public:
        typedef std::shared_ptr<Dice> Ptr;

        std::string Emoji;
        std::int32_t Value;
    };
}

#endif