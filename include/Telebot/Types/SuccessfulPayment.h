#ifndef Telebot_SuccessfulPaymentH
#define Telebot_SuccessfulPaymentH

#include "Telebot/Types/OrderInfo.h"

namespace Telebot
{
    class SuccessfulPayment
    {
    public:
        typedef std::shared_ptr<SuccessfulPayment> Ptr;

        std::string Currency;
        int TotalAmount;
        std::string InvoicePayload;
        std::string ShippingOptionId;
        OrderInfo::Ptr OrderInfo;
        std::string TelegramPaymentChargeId;
        std::string ProviderPaymentChargeId;
    };
}

#endif