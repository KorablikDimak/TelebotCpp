#ifndef Telebot_PassportElementErrorH
#define Telebot_PassportElementErrorH

#include <memory>
#include <string>

namespace Telebot
{
    class PassportElementError
    {
    public:
        typedef std::shared_ptr<PassportElementError> Ptr;

        PassportElementError() = default;
        virtual ~PassportElementError() = default;

        std::string Source;
        std::string Type;
        std::string Message;
    };
}

#endif