#ifndef Telebot_InputMediaPhotoH
#define Telebot_InputMediaPhotoH

#include "Telebot/Types/InputMedia.h"

namespace Telebot
{
    class InputMediaPhoto : public InputMedia
    {
    public:
        static const std::string TYPE;

        typedef std::shared_ptr<InputMediaPhoto> Ptr;

        InputMediaPhoto()
        {
            Type = TYPE;
        }

        bool HasSpoiler;
    };
}

#endif