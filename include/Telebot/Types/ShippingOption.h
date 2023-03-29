#ifndef Telebot_ShippingOptionH
#define Telebot_ShippingOptionH

#include <vector>

#include "LabeledPrice.h"

namespace Telebot
{
    class ShippingOption
    {
    public:
        typedef std::shared_ptr<ShippingOption> Ptr;

        std::string Id;
        std::string Title;
        std::vector<LabeledPrice::Ptr> Prices;
    };
}

#endif