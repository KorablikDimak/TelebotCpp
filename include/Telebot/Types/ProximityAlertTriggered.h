#ifndef Telebot_ProximityAlertTriggeredH
#define Telebot_ProximityAlertTriggeredH

#include "User.h"

namespace Telebot
{
    class ProximityAlertTriggered
    {
    public:
        typedef std::shared_ptr<ProximityAlertTriggered> Ptr;

        User::Ptr Traveler;
        User::Ptr Watcher;
        std::int32_t Distance;
    };
}

#endif