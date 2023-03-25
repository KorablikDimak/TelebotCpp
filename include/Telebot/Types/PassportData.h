#ifndef Telebot_PassportDataH
#define Telebot_PassportDataH

#include "Telebot/Types/EncryptedPassportElement.h"
#include "Telebot/Types/EncryptedCredentials.h"

namespace Telebot
{
    class PassportData
    {
    public:
        typedef std::shared_ptr<PassportData> Ptr;

        std::vector<EncryptedPassportElement::Ptr> Data;
        EncryptedCredentials::Ptr Credentials;
    };
}

#endif