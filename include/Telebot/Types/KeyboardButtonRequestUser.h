#ifndef Telebot_KeyboardButtonRequestUserH
#define Telebot_KeyboardButtonRequestUserH

#include <memory>

namespace Telebot
{
    class KeyboardButtonRequestUser
    {
    public:
        typedef std::shared_ptr<KeyboardButtonRequestUser> Ptr;

        std::int32_t RequestId;
        bool UserIsBot;
        bool UserIsPremium;
    };
}

#endif