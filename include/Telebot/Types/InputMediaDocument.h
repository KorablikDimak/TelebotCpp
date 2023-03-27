#ifndef Telebot_InputMediaDocumentH
#define Telebot_InputMediaDocumentH

#include "Telebot/Types/InputMedia.h"

namespace Telebot
{
    class InputMediaDocument : public InputMedia
    {
    public:
        static const std::string TYPE;

        typedef std::shared_ptr<InputMediaDocument> Ptr;

        InputMediaDocument()
        {
            Type = TYPE;
        }

        std::string Thumb;
        bool DisableContentTypeDetection;
    };
}

#endif