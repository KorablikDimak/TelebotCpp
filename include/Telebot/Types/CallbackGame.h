#ifndef Telebot_CallbackGameH
#define Telebot_CallbackGameH

#include <memory>

namespace Telebot
{
    class CallbackGame
    {
    public:
        typedef std::shared_ptr<CallbackGame> Ptr;
    };
}

#endif