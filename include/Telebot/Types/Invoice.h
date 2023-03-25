#ifndef Telebot_InvoiceH
#define Telebot_InvoiceH

#include <string>
#include <memory>

namespace Telebot
{
    class Invoice
    {
    public:
        typedef std::shared_ptr<Invoice> Ptr;

        std::string Title;
        std::string Description;
        std::string StartParameter;
        std::string Currency;
        int TotalAmount;
    };
}

#endif