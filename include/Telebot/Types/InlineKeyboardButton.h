#ifndef Telebot_InlineKeyboardButtonH
#define Telebot_InlineKeyboardButtonH

#include "WebAppInfo.h"
#include "LoginUrl.h"
#include "CallbackGame.h"

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