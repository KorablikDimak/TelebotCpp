#ifndef Telebot_ShippingQueryH
#define Telebot_ShippingQueryH

#include "Telebot/Types/User.h"
#include "Telebot/Types/ShippingAddress.h"

namespace Telebot
{
    class ShippingQuery
    {
    public:
        typedef std::shared_ptr<ShippingQuery> Ptr;

        std::string Id;
        User::Ptr From;
        std::string InvoicePayload;
        ShippingAddress::Ptr ShippingAddress;
    };
}

#endif