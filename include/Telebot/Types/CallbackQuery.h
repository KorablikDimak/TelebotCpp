#ifndef Telebot_CallbackQueryH
#define Telebot_CallbackQueryH

#include "User.h"
#include "Message.h"

namespace Telebot
{
    class CallbackQuery
    {
    public:
        typedef std::shared_ptr<CallbackQuery> Ptr;

        std::string Id;
        User::Ptr From;
        Message::Ptr Message;
        std::string InlineMessageId;
        std::string ChatInstance;
        std::string Data;
        std::string GameShortName;
    };
}

#endif