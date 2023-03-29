#ifndef Telebot_VIDEO_H
#define Telebot_VIDEO_H

#include "PhotoSize.h"

namespace Telebot
{
    class Video
    {
    public:
        typedef std::shared_ptr<Video> Ptr;

        std::string FileId;
        std::string FileUniqueId;
        std::int32_t Width;
        std::int32_t Height;
        std::int32_t Duration;
        PhotoSize::Ptr Thumb;
        std::string FileName;
        std::string MimeType;
        std::int64_t FileSize;
    };
}

#endif