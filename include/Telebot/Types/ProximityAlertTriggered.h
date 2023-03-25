#ifndef Telebot_ProximityAlertTriggeredH
#define Telebot_ProximityAlertTriggeredH

#include "Telebot/Types/User.h"

namespace Telebot
{
    class ProximityAlertTriggered
    {
    public:
        typedef std::shared_ptr<ProximityAlertTriggered> Ptr;

        User::Ptr Traveler;
        User::Ptr Watcher;
        int Distance;
    };
}

#endif