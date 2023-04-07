#ifndef Telebot_EncryptedCredentialsH
#define Telebot_EncryptedCredentialsH

#include "Telebot/JsonMacros.h"

namespace Telebot
{
    class EncryptedCredentials
    {
    public:
        typedef std::shared_ptr<EncryptedCredentials> Ptr;

        std::string data;
        std::string hash;
        std::string secret;
    };

    inline void from_json(const Json& json, EncryptedCredentials& object)
    {
        VALUE_FROM_JSON(data)
        VALUE_FROM_JSON(hash)
        VALUE_FROM_JSON(secret)
    }
}

#endif