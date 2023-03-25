#ifndef Telebot_ContactH
#define Telebot_ContactH

#include <string>
#include <memory>

namespace Telebot
{
    class Contact
    {
    public:
        typedef std::shared_ptr<Contact> Ptr;

        std::string PhoneNumber;
        std::string FirstName;
        std::string LastName;
        long long UserId;
        std::string Vcard;
    };
}

#endif