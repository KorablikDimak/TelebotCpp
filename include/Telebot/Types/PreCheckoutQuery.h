#ifndef Telebot_PreCheckoutQueryH
#define Telebot_PreCheckoutQueryH

#include "Telebot/Types/User.h"
#include "Telebot/Types/OrderInfo.h"

namespace Telebot
{
    class PreCheckoutQuery
    {
    public:
        typedef std::shared_ptr<PreCheckoutQuery> Ptr;

        std::string Id;
        User::Ptr From;
        std::string Currency;
        std::int32_t TotalAmount;
        std::string InvoicePayload;
        std::string ShippingOptionId;
        OrderInfo::Ptr OrderInfo;
    };
}

#endif