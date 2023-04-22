#ifndef Telebot_ContactH
#define Telebot_ContactH

#include "Common/JsonMacros.h"

namespace Telebot
{
    class Contact
    {
    public:
        typedef std::shared_ptr<Contact> Ptr;

        std::string phone_number;
        std::string first_name;
        std::string last_name;
        std::int64_t user_id;
        std::string vcard;
    };

    inline void from_json(const Json& json, Contact& object)
    {
        VALUE_FROM_JSON(phone_number)
        VALUE_FROM_JSON(first_name)
        VALUE_FROM_JSON(last_name)
        VALUE_FROM_JSON(user_id)
        VALUE_FROM_JSON(vcard)
    }
}

#endif