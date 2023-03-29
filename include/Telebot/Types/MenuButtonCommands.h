#ifndef Telebot_MenuButtonCommandsH
#define Telebot_MenuButtonCommandsH

#include "MenuButton.h"

namespace Telebot
{
    class MenuButtonCommands : public MenuButton
    {
    public:
        typedef std::shared_ptr<MenuButtonCommands> Ptr;

        static const std::string TYPE;

        MenuButtonCommands()
        {
            Type = TYPE;
        }
    };
}

#endif