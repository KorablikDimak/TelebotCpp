#ifndef Telebot_MenuButtonDefaultH
#define Telebot_MenuButtonDefaultH

#include "MenuButton.h"

namespace Telebot
{
    class MenuButtonDefault : public MenuButton
    {
    public:
        typedef std::shared_ptr<MenuButtonDefault> Ptr;

        static const std::string TYPE;

        MenuButtonDefault()
        {
            Type = TYPE;
        }
    };
}

#endif