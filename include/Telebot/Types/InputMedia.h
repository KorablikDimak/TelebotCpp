#ifndef Telebot_InputMediaH
#define Telebot_InputMediaH

#include <memory>
#include <string>
#include <vector>

#include "Telebot/Types/MessageEntity.h"

namespace Telebot
{
    class InputMedia
    {
    public:
        typedef std::shared_ptr<InputMedia> Ptr;

        InputMedia() = default;
        virtual ~InputMedia() = default;

        std::string Type;
        std::string Media;
        std::string Caption;
        std::string ParseMode;
        std::vector<MessageEntity::Ptr> CaptionEntities;
    };
}

#endif