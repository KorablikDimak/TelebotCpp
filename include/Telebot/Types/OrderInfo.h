#ifndef Telebot_OrderInfoH
#define Telebot_OrderInfoH

#include "ShippingAddress.h"

namespace Telebot
{
    class OrderInfo
    {
    public:
        typedef std::shared_ptr<OrderInfo> Ptr;

        std::string Name;
        std::string PhoneNumber;
        std::string Email;
        ShippingAddress::Ptr ShippingAddress;
    };
}

#endif