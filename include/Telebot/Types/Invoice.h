#ifndef Telebot_InvoiceH
#define Telebot_InvoiceH

#include "Common/JsonMacros.h"

namespace Telebot
{
    class Invoice
    {
    public:
        typedef std::shared_ptr<Invoice> Ptr;

        std::string title;
        std::string description;
        std::string start_parameter;
        std::string currency;
        std::int32_t total_amount;
    };

    inline void from_json(const Json& json, Invoice& object)
    {
        VALUE_FROM_JSON(title)
        VALUE_FROM_JSON(description)
        VALUE_FROM_JSON(start_parameter)
        VALUE_FROM_JSON(currency)
        VALUE_FROM_JSON(total_amount)
    }
}

#endif