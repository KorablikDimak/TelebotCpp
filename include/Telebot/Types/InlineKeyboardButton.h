#ifndef Telebot_InlineKeyboardButtonH
#define Telebot_InlineKeyboardButtonH

#include "Telebot/Types/WebAppInfo.h"
#include "Telebot/Types/LoginUrl.h"
#include "Telebot/Types/CallbackGame.h"

namespace Telebot
{
    class InlineKeyboardButton
    {
    public:
        typedef std::shared_ptr<InlineKeyboardButton> Ptr;

        std::string Text;
        std::string Url;
        std::string CallbackData;
        WebAppInfo::Ptr WebApp;
        LoginUrl::Ptr LoginUrl;
        std::string SwitchInlineQuery;
        std::string SwitchInlineQueryCurrentChat;
        CallbackGame::Ptr CallbackGame;
        bool Pay;
    };
}

#endif