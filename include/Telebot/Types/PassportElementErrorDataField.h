#ifndef Telebot_PassportElementErrorDataFieldH
#define Telebot_PassportElementErrorDataFieldH

#include "PassportElementError.h"

namespace Telebot
{
    class PassportElementErrorDataField : public PassportElementError
    {
    public:
        typedef std::shared_ptr<PassportElementErrorDataField> Ptr;

        static const std::string SOURCE;

        PassportElementErrorDataField()
        {
            Source = SOURCE;
        }

        std::string FieldName;
        std::string DataHash;
    };
}

#endif