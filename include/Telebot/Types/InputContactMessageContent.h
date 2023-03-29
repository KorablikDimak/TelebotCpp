#ifndef Telebot_InputContactMessageContentH
#define Telebot_InputContactMessageContentH

#include "InputMessageContent.h"

namespace Telebot
{
    class InputContactMessageContent : public InputMessageContent
    {
    public:
        typedef std::shared_ptr<InputContactMessageContent> Ptr;

        static const std::string TYPE;

        InputContactMessageContent()
        {
            Type = TYPE;
        }

        std::string PhoneNumber;
        std::string FirstName;
        std::string LastName;
        std::string Vcard;
    };
}

#endif