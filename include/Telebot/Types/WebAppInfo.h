#ifndef Telebot_WebAppInfoH
#define Telebot_WebAppInfoH

#include <memory>
#include <string>

namespace Telebot
{
    class WebAppInfo
    {
    public:
        typedef std::shared_ptr<WebAppInfo> Ptr;

        std::string Url;
    };
}

#endif