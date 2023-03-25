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
        int LivePeriod;
        int Heading;
        int ProximityAlertRadius;
    };
}

#endif