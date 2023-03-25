#ifndef Telebot_VIDEO_H
#define Telebot_VIDEO_H

#include "Telebot/Types/PhotoSize.h"

namespace Telebot
{
    class Video
    {
    public:
        typedef std::shared_ptr<Video> Ptr;

        std::string FileId;
        std::string FileUniqueId;
        int Width;
        int Height;
        int Duration;
        PhotoSize::Ptr Thumb;
        std::string FileName;
        std::string MimeType;
        long long FileSize;
    };
}

#endif