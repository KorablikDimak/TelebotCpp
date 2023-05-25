#ifndef Telebot_LoginUrlH
#define Telebot_LoginUrlH

#include "Common/JsonMacros.h"

namespace Telebot
{
    class LoginUrl
    {
    public:
        typedef std::shared_ptr<LoginUrl> Ptr;

        std::string url;
        std::string forward_text;
        std::string bot_username;
        bool request_write_access;
    };

    inline void from_json(const Json& json, LoginUrl& object)
    {
        VALUE_FROM_JSON(url)
        VALUE_FROM_JSON(forward_text)
        VALUE_FROM_JSON(bot_username)
        VALUE_FROM_JSON(request_write_access)
    }

    inline void to_json(Json& json, const LoginUrl::Ptr& object)
    {
        VALUE_TO_JSON(url)
        if (!object->forward_text.empty()) VALUE_TO_JSON(forward_text)
        if (!object->bot_username.empty()) VALUE_TO_JSON(bot_username)
        VALUE_TO_JSON(request_write_access)
    }
}

#endif