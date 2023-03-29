#ifndef Telebot_ChatLocationH
#define Telebot_ChatLocationH

#include "Location.h"

namespace Telebot
{
    class ChatLocation
    {
    public:
        typedef std::shared_ptr<ChatLocation> Ptr;

        Location::Ptr Location;
        std::string Address;
    };
}

#endif