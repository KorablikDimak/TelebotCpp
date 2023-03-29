#ifndef Telebot_InputMediaAudioH
#define Telebot_InputMediaAudioH

#include "InputMedia.h"

namespace Telebot
{
    class InputMediaAudio : public InputMedia
    {
    public:
        typedef std::shared_ptr<InputMediaAudio> Ptr;

        static const std::string TYPE;

        InputMediaAudio()
        {
            Type = TYPE;
        }

        std::string Thumb;
        std::int32_t Duration;
        std::string Performer;
        std::string Title;
    };
}

#endif