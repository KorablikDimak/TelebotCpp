#ifndef Telebot_PassportDataH
#define Telebot_PassportDataH

#include "EncryptedPassportElement.h"
#include "EncryptedCredentials.h"

namespace Telebot
{
    class PassportData
    {
    public:
        typedef std::shared_ptr<PassportData> Ptr;

        std::vector<EncryptedPassportElement::Ptr> data;
        EncryptedCredentials::Ptr credentials;
    };

    inline void from_json(const Json& json, PassportData& object)
    {
        OBJECTS_FROM_JSON(data)
        OBJECT_FROM_JSON(credentials)
    }
}

#endif