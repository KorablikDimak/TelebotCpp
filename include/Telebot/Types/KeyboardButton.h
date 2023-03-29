#ifndef Telebot_KeyboardButtonH
#define Telebot_KeyboardButtonH

#include "KeyboardButtonRequestUser.h"
#include "KeyboardButtonRequestChat.h"
#include "KeyboardButtonPollType.h"
#include "WebAppInfo.h"

namespace Telebot
{
    class KeyboardButton
    {
    public:
        typedef std::shared_ptr<KeyboardButton> Ptr;

        std::string Text;
        KeyboardButtonRequestUser::Ptr RequestUser;
        KeyboardButtonRequestChat::Ptr RequestChat;
        bool RequestContact;
        bool RequestLocation;
        KeyboardButtonPollType::Ptr RequestPoll;
        WebAppInfo::Ptr WebApp;
    };
}

#endif