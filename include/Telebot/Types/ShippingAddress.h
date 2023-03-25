#ifndef Telebot_ShippingAddressH
#define Telebot_ShippingAddressH

#include <string>
#include <memory>

namespace Telebot
{
    class ShippingAddress
    {
    public:
        typedef std::shared_ptr<ShippingAddress> Ptr;

        std::string CountryCode;
        std::string State;
        std::string City;
        std::string StreetLine1;
        std::string StreetLine2;
        std::string PostCode;
    };
}

#endif