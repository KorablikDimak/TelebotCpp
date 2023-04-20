#ifndef Telebot_BotCommandH
#define Telebot_BotCommandH

#include "Telebot/JsonMacros.h"

namespace Telebot
{
    class BotCommand
    {
    public:
        typedef std::shared_ptr<BotCommand> Ptr;

        BotCommand() = default;

        BotCommand(std::string command, std::string description)
        {
            this->command = command;
            this->description = description;
        }

        virtual ~BotCommand() = default;

        std::string command;
        std::string description;
    };

    inline void from_json(const Json& json, BotCommand& object)
    {
        VALUE_FROM_JSON(command)
        VALUE_FROM_JSON(description)
    }

    inline void to_json(Json& json, const BotCommand::Ptr& object)
    {
        VALUE_TO_JSON(command)
        VALUE_TO_JSON(description)
    }
}

#endif