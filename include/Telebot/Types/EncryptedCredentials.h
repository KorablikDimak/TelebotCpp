#ifndef Telebot_EncryptedCredentialsH
#define Telebot_EncryptedCredentialsH

#include <memory>
#include <string>

namespace Telebot
{
    class EncryptedCredentials
    {
    public:
        typedef std::shared_ptr<EncryptedCredentials> Ptr;

        std::string Data;
        std::string Hash;
        std::string Secret;
    };
}

#endif