#ifndef Telebot_PassportElementErrorReverseSideH
#define Telebot_PassportElementErrorReverseSideH

#include "PassportElementError.h"

namespace Telebot
{
    class PassportElementErrorReverseSide : public PassportElementError
    {
    public:
        typedef std::shared_ptr<PassportElementErrorReverseSide> Ptr;

        static const std::string SOURCE;

        PassportElementErrorReverseSide()
        {
            Source = SOURCE;
        }

        std::string FileHash;
    };
}

#endif