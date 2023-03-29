#ifndef Telebot_InputMediaVideoH
#define Telebot_InputMediaVideoH

#include "InputMedia.h"
#include "InputFile.h"

namespace Telebot
{
    class InputMediaVideo : public InputMedia
    {
    public:
        typedef std::shared_ptr<InputMediaVideo> Ptr;

        static const std::string TYPE;

        InputMediaVideo()
        {
            Type = TYPE;
        }

        std::string Thumb;
        std::int32_t Width;
        std::int32_t Height;
        std::int32_t Duration;
        bool SupportsStreaming;
        bool HasSpoiler;
    };
}

#endif