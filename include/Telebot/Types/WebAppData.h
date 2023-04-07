#ifndef Telebot_WebAppDataH
#define Telebot_WebAppDataH

#include "Telebot/JsonMacros.h"

namespace Telebot
{
    class WebAppData
    {
    public:
        typedef std::shared_ptr<WebAppData> Ptr;

        std::string data;
        std::string button_text;
    };

    inline void from_json(const Json& json, WebAppData& object)
    {
        VALUE_FROM_JSON(data)
        VALUE_FROM_JSON(button_text)
    }
}

#endif