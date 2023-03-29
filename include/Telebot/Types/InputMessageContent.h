#ifndef Telebot_InputMessageContentH
#define Telebot_InputMessageContentH

#include <memory>
#include <string>

namespace Telebot
{
    class InputMessageContent
    {
    public:
        typedef std::shared_ptr<InputMessageContent> Ptr;

        InputMessageContent() = default;
        virtual ~InputMessageContent() = default;

        std::string Type;
    };
}

#endif