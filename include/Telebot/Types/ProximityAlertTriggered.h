#ifndef Telebot_ProximityAlertTriggeredH
#define Telebot_ProximityAlertTriggeredH

#include "User.h"

namespace Telebot
{
    class ProximityAlertTriggered
    {
    public:
        typedef std::shared_ptr<ProximityAlertTriggered> Ptr;

        User::Ptr traveler;
        User::Ptr watcher;
        std::int32_t distance;
    };

    inline void from_json(const Json& json, ProximityAlertTriggered& object)
    {
        OBJECT_FROM_JSON(traveler)
        OBJECT_FROM_JSON(watcher)
        VALUE_FROM_JSON(distance)
    }
}

#endif