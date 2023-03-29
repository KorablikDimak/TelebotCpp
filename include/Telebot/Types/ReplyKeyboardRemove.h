#ifndef Telebot_ReplyKeyboardRemoveH
#define Telebot_ReplyKeyboardRemoveH

#include "GenericReply.h"

namespace Telebot
{
    class ReplyKeyboardRemove : public GenericReply
    {
    public:
        typedef std::shared_ptr<ReplyKeyboardRemove> Ptr;

        bool RemoveKeyboard;
        bool Selective;
    };
}

#endif