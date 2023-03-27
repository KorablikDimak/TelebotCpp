#ifndef Telebot_MenuButtonDefaultH
#define Telebot_MenuButtonDefaultH

#include "Telebot/Types/MenuButton.h"

namespace Telebot
{
    class MenuButtonDefault : public MenuButton
    {
    public:
        static const std::string TYPE;

        typedef std::shared_ptr<MenuButtonDefault> Ptr;

        MenuButtonDefault()
        {
            Type = TYPE;
        }
    };
}

#endif