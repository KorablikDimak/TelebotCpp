#ifndef Telebot_PassportElementErrorTranslationFileH
#define Telebot_PassportElementErrorTranslationFileH

#include "PassportElementError.h"

namespace Telebot
{
    class PassportElementErrorTranslationFile : public PassportElementError
    {
    public:
        typedef std::shared_ptr<PassportElementErrorTranslationFile> Ptr;

        static const std::string SOURCE;

        PassportElementErrorTranslationFile()
        {
            Source = SOURCE;
        }

        std::string FileHash;
    };
}

#endif