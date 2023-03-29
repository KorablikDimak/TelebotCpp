#ifndef Telebot_VoiceH
#define Telebot_VoiceH

#include <memory>
#include <string>

namespace Telebot
{
    class Voice
    {
    public:
        typedef std::shared_ptr<Voice> Ptr;

        std::string FileId;
        std::string FileUniqueId;
        std::int32_t Duration;
        std::string MimeType;
        std::int64_t FileSize;
    };
}

#endif