#ifndef Telebot_InputInvoiceMessageContentH
#define Telebot_InputInvoiceMessageContentH

#include <vector>

#include "InputMessageContent.h"
#include "LabeledPrice.h"

namespace Telebot
{
    class InputInvoiceMessageContent : public InputMessageContent
    {
    public:
        typedef std::shared_ptr<InputInvoiceMessageContent> Ptr;

        static const std::string TYPE;

        InputInvoiceMessageContent()
        {
            Type = TYPE;
        }

        std::string Title;
        std::string Description;
        std::string Payload;
        std::string ProviderToken;
        std::string Currency;
        std::vector<LabeledPrice::Ptr> Prices;
        std::int32_t MaxTipAmount;
        std::vector<std::int32_t> SuggestedTipAmounts;
        std::string ProviderData;
        std::string PhotoUrl;
        std::int32_t PhotoSize;
        std::int32_t PhotoWidth;
        std::int32_t PhotoHeight;
        bool NeedName;
        bool NeedPhoneNumber;
        bool NeedEmail;
        bool NeedShippingAddress;
        bool SendPhoneNumberToProvider;
        bool SendEmailToProvider;
        bool IsFlexible;
    };
}

#endif