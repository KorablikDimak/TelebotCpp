#ifndef Telebot_AudioH
#define Telebot_AudioH

#include "PhotoSize.h"

namespace Telebot
{
    class Audio
    {
    public:
        typedef std::shared_ptr<Audio> Ptr;

        std::string FileId;
        std::string FileUniqueId;
        std::int32_t Duration;
        std::string Performer;
        std::string Title;
        std::string FileName;
        std::string MimeType;
        std::int64_t FileSize;
        PhotoSize::Ptr Thumb;
    };
}

#endif