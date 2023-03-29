#ifndef Telebot_PassportElementErrorFilesH
#define Telebot_PassportElementErrorFilesH

#include <vector>

#include "PassportElementError.h"

namespace Telebot
{
    class PassportElementErrorFiles : public PassportElementError
    {
    public:
        typedef std::shared_ptr<PassportElementErrorFiles> Ptr;

        static const std::string SOURCE;

        PassportElementErrorFiles()
        {
            Source = SOURCE;
        }

        std::vector<std::string> FileHashes;
    };
}

#endif