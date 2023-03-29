#ifndef Telebot_InputMediaPhotoH
#define Telebot_InputMediaPhotoH

#include "InputMedia.h"

namespace Telebot
{
    class InputMediaPhoto : public InputMedia
    {
    public:
        typedef std::shared_ptr<InputMediaPhoto> Ptr;

        static const std::string TYPE;

        InputMediaPhoto()
        {
            Type = TYPE;
        }

        bool HasSpoiler;
    };
}

#endif