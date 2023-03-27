#ifndef Telebot_MenuButtonWebAppH
#define Telebot_MenuButtonWebAppH

#include "Telebot/Types/MenuButton.h"
#include "Telebot/Types/WebAppInfo.h"

namespace Telebot
{
    class MenuButtonWebApp : public MenuButton
    {
    public:
        static const std::string TYPE;

        typedef std::shared_ptr<MenuButtonWebApp> Ptr;

        MenuButtonWebApp()
        {
            Type = TYPE;
        }

        std::string Text;
        WebAppInfo::Ptr WebApp;
    };
}

#endif