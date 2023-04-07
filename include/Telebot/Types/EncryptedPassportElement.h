#ifndef Telebot_EncryptedPassportElementH
#define Telebot_EncryptedPassportElementH

#include "PassportFile.h"

namespace Telebot
{
    class EncryptedPassportElement
    {
    public:
        typedef std::shared_ptr<EncryptedPassportElement> Ptr;

        std::string type;
        std::string data;
        std::string phone_number;
        std::string email;
        std::vector<PassportFile::Ptr> files;
        PassportFile::Ptr front_side;
        PassportFile::Ptr reverse_side;
        PassportFile::Ptr selfie;
        std::vector<PassportFile::Ptr> translation;
        std::string hash;
    };

    inline void from_json(const Json& json, EncryptedPassportElement& object)
    {
        VALUE_FROM_JSON(type)
        VALUE_FROM_JSON(data)
        VALUE_FROM_JSON(phone_number)
        VALUE_FROM_JSON(email)
        OBJECTS_FROM_JSON(files)
        OBJECT_FROM_JSON(front_side)
        OBJECT_FROM_JSON(reverse_side)
        OBJECT_FROM_JSON(selfie)
        OBJECTS_FROM_JSON(translation)
        VALUE_FROM_JSON(hash)
    }
}

#endif