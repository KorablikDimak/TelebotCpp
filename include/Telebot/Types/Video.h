#ifndef Telebot_VIDEO_H
#define Telebot_VIDEO_H

#include "PhotoSize.h"

namespace Telebot
{
    class Video
    {
    public:
        typedef std::shared_ptr<Video> Ptr;

        std::string file_id;
        std::string file_unique_id;
        std::int32_t width;
        std::int32_t height;
        std::int32_t duration;
        PhotoSize::Ptr thumb;
        std::string file_name;
        std::string mime_type;
        std::int64_t file_size;
    };

    inline void from_json(const Json& json, Video& object)
    {
        VALUE_FROM_JSON(file_id)
        VALUE_FROM_JSON(file_unique_id)
        VALUE_FROM_JSON(width)
        VALUE_FROM_JSON(height)
        VALUE_FROM_JSON(duration)
        OBJECT_FROM_JSON(thumb)
        VALUE_FROM_JSON(file_name)
        VALUE_FROM_JSON(mime_type)
        VALUE_FROM_JSON(file_size)
    }
}

#endif