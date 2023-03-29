#ifndef Telebot_PassportElementErrorTranslationFilesH
#define Telebot_PassportElementErrorTranslationFilesH

#include <vector>

#include "PassportElementError.h"

namespace Telebot
{
    class PassportElementErrorTranslationFiles : public PassportElementError
    {
    public:
        typedef std::shared_ptr<PassportElementErrorTranslationFiles> Ptr;

        static const std::string SOURCE;

        PassportElementErrorTranslationFiles()
        {
            Source = SOURCE;
        }

        std::vector<std::string> FileHashes;
    };
}

#endif