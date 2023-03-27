#ifndef Telebot_BotCommandH
#define Telebot_BotCommandH

#include <string>
#include <memory>

namespace Telebot
{
    class BotCommand
    {
    public:
        typedef std::shared_ptr<BotCommand> Ptr;

        BotCommand() = default;
        virtual ~BotCommand() = default;

        std::string Command;
        std::string Description;

    };
}

#endif