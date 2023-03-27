#ifndef Telebot_MenuButtonCommandsH
#define Telebot_MenuButtonCommandsH

#include "Telebot/Types/MenuButton.h"

namespace Telebot
{
    class MenuButtonCommands : public MenuButton
    {
    public:
        static const std::string TYPE;

        typedef std::shared_ptr<MenuButtonCommands> Ptr;

        MenuButtonCommands()
        {
            Type = TYPE;
        }
    };
}

#endif