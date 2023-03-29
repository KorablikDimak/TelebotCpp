#ifndef Telebot_VideoNoteH
#define Telebot_VideoNoteH

#include "PhotoSize.h"

namespace Telebot
{
    class VideoNote
    {
    public:
        typedef std::shared_ptr<VideoNote> Ptr;

        std::string FileId;
        std::string FileUniqueId;
        std::int32_t Length;
        std::int32_t Duration;
        PhotoSize::Ptr Thumb;
        std::int32_t FileSize;
    };
}

#endif
