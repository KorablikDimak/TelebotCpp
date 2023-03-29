#ifndef Telebot_KeyboardButtonPollTypeH
#define Telebot_KeyboardButtonPollTypeH

#include <string>
#include <memory>

namespace Telebot
{
    class KeyboardButtonPollType
    {
    public:
        typedef std::shared_ptr<KeyboardButtonPollType> Ptr;

        std::string Type;
    };
}

#endif