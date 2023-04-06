#ifndef Telebot_OrderInfoH
#define Telebot_OrderInfoH

#include "ShippingAddress.h"

namespace Telebot
{
    class OrderInfo
    {
    public:
        typedef std::shared_ptr<OrderInfo> Ptr;

        std::string name;
        std::string phone_number;
        std::string email;
        ShippingAddress::Ptr shipping_address;
    };

    void from_json(const Json& json, OrderInfo& orderInfo)
    {
        VALUE_FROM_JSON(name)
        VALUE_FROM_JSON(phone_number)
        VALUE_FROM_JSON(email)
        OBJECT_FROM_JSON(shipping_address)
    }
}

#endif