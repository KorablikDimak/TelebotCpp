#ifndef Telebot_EncryptedPassportElementH
#define Telebot_EncryptedPassportElementH

#include "PassportFile.h"

namespace Telebot
{
    class EncryptedPassportElement
    {
    public:
        typedef std::shared_ptr<EncryptedPassportElement> Ptr;

        std::string Type;
        std::string Data;
        std::string PhoneNumber;
        std::string Email;
        std::vector<PassportFile::Ptr> Files;
        PassportFile::Ptr FrontSide;
        PassportFile::Ptr ReverseSide;
        PassportFile::Ptr Selfie;
        std::vector<PassportFile::Ptr> Translation;
        std::string Hash;
    };
}

#endif