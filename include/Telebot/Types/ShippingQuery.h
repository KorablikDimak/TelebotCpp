#ifndef Telebot_ShippingQueryH
#define Telebot_ShippingQueryH

#include "User.h"
#include "ShippingAddress.h"

namespace Telebot
{
    class ShippingQuery
    {
    public:
        typedef std::shared_ptr<ShippingQuery> Ptr;

        std::string id;
        User::Ptr from;
        std::string invoice_payload;
        ShippingAddress::Ptr shipping_address;
    };

    void from_json(const Json& json, ShippingQuery& object)
    {
        VALUE_FROM_JSON(id)
        OBJECT_FROM_JSON(from)
        VALUE_FROM_JSON(invoice_payload)
        OBJECT_FROM_JSON(shipping_address)
    }
}

#endif