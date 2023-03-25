#ifndef Telebot_AudioH
#define Telebot_AudioH

#include "Telebot/Types/PhotoSize.h"

namespace Telebot
{
    class Audio
    {
    public:
        typedef std::shared_ptr<Audio> Ptr;

        std::string FileId;
        std::string FileUniqueId;
        int Duration;
        std::string Performer;
        std::string Title;
        std::string FileName;
        std::string MimeType;
        long long FileSize;
        PhotoSize::Ptr Thumb;
    };
}

#endif