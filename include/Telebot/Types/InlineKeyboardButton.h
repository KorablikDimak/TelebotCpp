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

        std::string text;
        std::string url;
        std::string callback_data;
        WebAppInfo::Ptr web_app;
        LoginUrl::Ptr login_url;
        std::string switch_inline_query;
        std::string switch_inline_query_current_chat;
        CallbackGame::Ptr callback_game;
        bool pay;
    };

    inline void from_json(const Json& json, InlineKeyboardButton& object)
    {
        VALUE_FROM_JSON(text)
        VALUE_FROM_JSON(url)
        VALUE_FROM_JSON(callback_data)
        OBJECT_FROM_JSON(web_app)
        OBJECT_FROM_JSON(login_url)
        VALUE_FROM_JSON(switch_inline_query)
        VALUE_FROM_JSON(switch_inline_query_current_chat)
        OBJECT_FROM_JSON(callback_game)
        VALUE_FROM_JSON(pay)
    }
}

#endif