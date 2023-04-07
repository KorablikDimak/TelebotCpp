#ifndef Telebot_AudioH
#define Telebot_AudioH

#include "PhotoSize.h"

namespace Telebot
{
    class Audio
    {
    public:
        typedef std::shared_ptr<Audio> Ptr;

        std::string file_id;
        std::string file_unique_id;
        std::int32_t duration;
        std::string performer;
        std::string title;
        std::string file_name;
        std::string mime_type;
        std::int64_t file_size;
        PhotoSize::Ptr thumb;
    };

    inline void from_json(const Json& json, Audio& object)
    {
        VALUE_FROM_JSON(file_id)
        VALUE_FROM_JSON(file_unique_id)
        VALUE_FROM_JSON(duration)
        VALUE_FROM_JSON(performer)
        VALUE_FROM_JSON(title)
        VALUE_FROM_JSON(file_name)
        VALUE_FROM_JSON(mime_type)
        VALUE_FROM_JSON(file_size)
        OBJECT_FROM_JSON(thumb)
    }
}

#endif