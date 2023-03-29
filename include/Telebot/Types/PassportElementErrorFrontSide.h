#ifndef Telebot_PassportElementErrorFrontSideH
#define Telebot_PassportElementErrorFrontSideH

#include "PassportElementError.h"

namespace Telebot
{
    class PassportElementErrorFrontSide : public PassportElementError
    {
    public:
        typedef std::shared_ptr<PassportElementErrorFrontSide> Ptr;

        static const std::string SOURCE;

        PassportElementErrorFrontSide()
        {
            Source = SOURCE;
        }

        std::string FileHash;
    };
}

#endif