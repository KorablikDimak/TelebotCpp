#ifndef Telebot_LocationH
#define Telebot_LocationH

#include <memory>

namespace Telebot
{
    class Location
    {
    public:
        typedef std::shared_ptr<Location> Ptr;

        float Longitude;
        float Latitude;
        float HorizontalAccuracy;
        std::int32_t LivePeriod;
        std::int32_t Heading;
        std::int32_t ProximityAlertRadius;
    };
}

#endif