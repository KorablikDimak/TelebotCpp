#ifndef Telebot_SuccessfulPaymentH
#define Telebot_SuccessfulPaymentH

#include "OrderInfo.h"

namespace Telebot
{
    class SuccessfulPayment
    {
    public:
        typedef std::shared_ptr<SuccessfulPayment> Ptr;

        std::string Currency;
        std::int32_t TotalAmount;
        std::string InvoicePayload;
        std::string ShippingOptionId;
        OrderInfo::Ptr OrderInfo;
        std::string TelegramPaymentChargeId;
        std::string ProviderPaymentChargeId;
    };
}

#endif