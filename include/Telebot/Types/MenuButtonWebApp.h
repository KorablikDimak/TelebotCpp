#ifndef Telebot_MenuButtonWebAppH
#define Telebot_MenuButtonWebAppH

#include "MenuButton.h"
#include "WebAppInfo.h"

namespace Telebot
{
    class MenuButtonWebApp : public MenuButton
    {
    public:
        typedef std::shared_ptr<MenuButtonWebApp> Ptr;

        static const std::string TYPE;

        MenuButtonWebApp()
        {
            Type = TYPE;
        }

        std::string Text;
        WebAppInfo::Ptr WebApp;
    };
}

#endif