#ifndef Telebot_WebAppInfoH
#define Telebot_WebAppInfoH

#include "Common/JsonMacros.h"

namespace Telebot
{
    class WebAppInfo
    {
    public:
        typedef std::shared_ptr<WebAppInfo> Ptr;

        std::string url;
    };

    inline void from_json(const Json& json, WebAppInfo& object)
    {
        VALUE_FROM_JSON(url)
    }

    inline void to_json(Json& json, const WebAppInfo::Ptr& object)
    {
        VALUE_TO_JSON(url)
    }
}

#endif