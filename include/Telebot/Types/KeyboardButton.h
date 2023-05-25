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

        std::string text;
        KeyboardButtonRequestUser::Ptr request_user;
        KeyboardButtonRequestChat::Ptr request_chat;
        bool request_contact;
        bool request_location;
        KeyboardButtonPollType::Ptr request_poll;
        WebAppInfo::Ptr web_app;
    };

    inline void to_json(Json& json, const KeyboardButton::Ptr& object)
    {
        VALUE_TO_JSON(text)
        OBJECT_TO_JSON(request_user)
        OBJECT_TO_JSON(request_chat)
        VALUE_TO_JSON(request_contact)
        VALUE_TO_JSON(request_location)
        OBJECT_TO_JSON(request_poll)
        OBJECT_TO_JSON(web_app)
    }
}

#endif