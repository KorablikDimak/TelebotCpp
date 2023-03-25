#ifndef Telebot_WebAppDataH
#define Telebot_WebAppDataH

#include <memory>
#include <string>

namespace Telebot
{
    class WebAppData
    {
    public:
        typedef std::shared_ptr<WebAppData> Ptr;

        std::string Data;
        std::string ButtonText;
    };
}

#endif