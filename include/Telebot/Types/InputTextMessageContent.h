#ifndef Telebot_InputTextMessageContentH
#define Telebot_InputTextMessageContentH

#include <vector>

#include "InputMessageContent.h"
#include "MessageEntity.h"

namespace Telebot
{
    class InputTextMessageContent : public InputMessageContent
    {
    public:
        typedef std::shared_ptr<InputTextMessageContent> Ptr;

        static const std::string TYPE;

        InputTextMessageContent()
        {
            Type = TYPE;
        }

        std::string MessageText;
        std::string ParseMode;
        std::vector<MessageEntity::Ptr> Entities;
        bool DisableWebPagePreview;
    };
}

#endif