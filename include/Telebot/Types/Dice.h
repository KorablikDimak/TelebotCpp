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
        int Value;
    };
}

#endif