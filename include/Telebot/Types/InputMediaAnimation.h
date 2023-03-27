#ifndef Telebot_InputMediaAnimationH
#define Telebot_InputMediaAnimationH

#include "Telebot/Types/InputMedia.h"

namespace Telebot
{
    class InputMediaAnimation : public InputMedia
    {
    public:
        static const std::string TYPE;

        typedef std::shared_ptr<InputMediaAnimation> Ptr;

        InputMediaAnimation()
        {
            Type = TYPE;
        }

        std::string Thumb;
        std::int32_t Width;
        std::int32_t Height;
        std::int32_t Duration;
        bool HasSpoiler;
    };
}

#endif