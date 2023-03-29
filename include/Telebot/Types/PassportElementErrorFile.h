#ifndef Telebot_PassportElementErrorFileH
#define Telebot_PassportElementErrorFileH

#include "PassportElementError.h"

namespace Telebot
{
    class PassportElementErrorFile : public PassportElementError
    {
    public:
        typedef std::shared_ptr<PassportElementErrorFile> Ptr;

        static const std::string SOURCE;

        PassportElementErrorFile()
        {
            Source = SOURCE;
        }

        std::string FileHash;
    };
}

#endif