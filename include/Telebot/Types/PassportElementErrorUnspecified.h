#ifndef Telebot_PassportElementErrorUnspecifiedH
#define Telebot_PassportElementErrorUnspecifiedH

#include "PassportElementError.h"

namespace Telebot
{
    class PassportElementErrorUnspecified : public PassportElementError
    {
    public:
        typedef std::shared_ptr<PassportElementErrorUnspecified> Ptr;

        static const std::string SOURCE;

        PassportElementErrorUnspecified()
        {
            Source = SOURCE;
        }

        std::string ElementHash;
    };
}

#endif