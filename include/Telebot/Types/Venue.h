#ifndef Telebot_VenueH
#define Telebot_VenueH

#include "Location.h"

namespace Telebot
{
    class Venue
    {
    public:
        typedef std::shared_ptr<Venue> Ptr;

        Location::Ptr location;
        std::string title;
        std::string address;
        std::string foursquare_id;
        std::string foursquare_type;
        std::string google_place_id;
        std::string google_place_type;
    };

    inline void from_json(const Json& json, Venue& object)
    {
        OBJECT_FROM_JSON(location)
        VALUE_FROM_JSON(title)
        VALUE_FROM_JSON(address)
        VALUE_FROM_JSON(foursquare_id)
        VALUE_FROM_JSON(foursquare_type)
        VALUE_FROM_JSON(google_place_id)
        VALUE_FROM_JSON(google_place_type)
    }
}

#endif