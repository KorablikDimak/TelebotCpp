#ifndef Telebot_AnimationH
#define Telebot_AnimationH

#include "PhotoSize.h"

namespace Telebot
{
    class Animation
    {
    public:
        typedef std::shared_ptr<Animation> Ptr;

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