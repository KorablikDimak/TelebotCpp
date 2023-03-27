#ifndef Telebot_InputMediaAudioH
#define Telebot_InputMediaAudioH

#include "Telebot/Types/InputMedia.h"

namespace Telebot
{
    class InputMediaAudio : public InputMedia
    {
    public:
        static const std::string TYPE;

        typedef std::shared_ptr<InputMediaAudio> Ptr;

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