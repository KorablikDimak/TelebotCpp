#ifndef Telebot_AnimationH
#define Telebot_AnimationH

#include "Telebot/Types/PhotoSize.h"

namespace Telebot
{
    class Animation
    {
    public:
        typedef std::shared_ptr<Animation> Ptr;

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