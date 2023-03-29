#ifndef Telebot_VenueH
#define Telebot_VenueH

#include "Location.h"

namespace Telebot
{
    class Venue
    {
    public:
        typedef std::shared_ptr<Venue> Ptr;

        Location::Ptr Location;
        std::string Title;
        std::string Address;
        std::string FoursquareId;
        std::string FoursquareType;
        std::string GooglePlaceId;
        std::string GooglePlaceType;
    };
}

#endif