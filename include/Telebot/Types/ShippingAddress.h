#ifndef Telebot_ShippingAddressH
#define Telebot_ShippingAddressH

#include "Telebot/JsonMacros.h"

namespace Telebot
{
    class ShippingAddress
    {
    public:
        typedef std::shared_ptr<ShippingAddress> Ptr;

        std::string country_code;
        std::string state;
        std::string city;
        std::string street_line1;
        std::string street_line2;
        std::string post_code;
    };

    inline void from_json(const Json& json, ShippingAddress& object)
    {
        VALUE_FROM_JSON(country_code)
        VALUE_FROM_JSON(state)
        VALUE_FROM_JSON(city)
        VALUE_FROM_JSON(street_line1)
        VALUE_FROM_JSON(street_line2)
        VALUE_FROM_JSON(post_code)
    }
}

#endif