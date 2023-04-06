#ifndef Telebot_PreCheckoutQueryH
#define Telebot_PreCheckoutQueryH

#include "User.h"
#include "OrderInfo.h"

namespace Telebot
{
    class PreCheckoutQuery
    {
    public:
        typedef std::shared_ptr<PreCheckoutQuery> Ptr;

        std::string id;
        User::Ptr from;
        std::string currency;
        std::int32_t total_amount;
        std::string invoice_payload;
        std::string shipping_option_id;
        OrderInfo::Ptr order_info;
    };

    void from_json(const Json& json, PreCheckoutQuery& object)
    {
        VALUE_FROM_JSON(id)
        OBJECT_FROM_JSON(from)
        VALUE_FROM_JSON(currency)
        VALUE_FROM_JSON(total_amount)
        VALUE_FROM_JSON(invoice_payload)
        VALUE_FROM_JSON(shipping_option_id)
        OBJECT_FROM_JSON(order_info)
    }
}

#endif