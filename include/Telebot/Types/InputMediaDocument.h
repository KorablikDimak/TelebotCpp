#ifndef Telebot_InputMediaDocumentH
#define Telebot_InputMediaDocumentH

#include "InputMedia.h"

namespace Telebot
{
    class InputMediaDocument : public InputMedia
    {
    public:
        typedef std::shared_ptr<InputMediaDocument> Ptr;

        static const std::string TYPE;

        InputMediaDocument()
        {
            Type = TYPE;
        }

        std::string Thumb;
        bool DisableContentTypeDetection;
    };
}

#endif