#ifndef Telebot_InputMediaVideoH
#define Telebot_InputMediaVideoH

#include "Telebot/Types/InputMedia.h"
#include "Telebot/Types/InputFile.h"

namespace Telebot
{
    class InputMediaVideo : public InputMedia
    {
    public:
        static const std::string TYPE;

        typedef std::shared_ptr<InputMediaVideo> Ptr;

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