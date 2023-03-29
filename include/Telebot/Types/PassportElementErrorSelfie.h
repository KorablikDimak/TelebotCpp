#ifndef Telebot_PassportElementErrorSelfieH
#define Telebot_PassportElementErrorSelfieH

#include "PassportElementError.h"

namespace Telebot
{
    class PassportElementErrorSelfie : public PassportElementError
    {
    public:
        typedef std::shared_ptr<PassportElementErrorSelfie> Ptr;

        static const std::string SOURCE;

        PassportElementErrorSelfie()
        {
            Source = SOURCE;
        }

        std::string FileHash;
    };
}

#endif