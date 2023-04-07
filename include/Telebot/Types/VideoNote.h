#ifndef Telebot_VideoNoteH
#define Telebot_VideoNoteH

#include "PhotoSize.h"

namespace Telebot
{
    class VideoNote
    {
    public:
        typedef std::shared_ptr<VideoNote> Ptr;

        std::string file_id;
        std::string file_unique_id;
        std::int32_t length;
        std::int32_t duration;
        PhotoSize::Ptr thumb;
        std::int32_t file_size;
    };

    inline void from_json(const Json& json, VideoNote& object)
    {
        VALUE_FROM_JSON(file_id)
        VALUE_FROM_JSON(file_unique_id)
        VALUE_FROM_JSON(length)
        VALUE_FROM_JSON(duration)
        OBJECT_FROM_JSON(thumb)
        VALUE_FROM_JSON(file_size)
    }
}

#endif
