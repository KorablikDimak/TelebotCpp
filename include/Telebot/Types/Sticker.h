#ifndef Telebot_StickerH
#define Telebot_StickerH

#include "PhotoSize.h"
#include "File.h"
#include "MaskPosition.h"

namespace Telebot
{
    class Sticker
    {
    public:
        typedef std::shared_ptr<Sticker> Ptr;

        enum class Type
        {
            regular, mask, custom_emoji
        };

        std::string file_id;
        std::string file_unique_id;
        std::string type;
        std::int32_t width;
        std::int32_t height;
        bool is_animated;
        bool is_video;
        PhotoSize::Ptr thumb;
        std::string emoji;
        std::string set_name;
        File::Ptr premium_animation;
        MaskPosition::Ptr mask_position;
        std::string custom_emoji_id;
        std::int32_t file_size;
    };

    inline void from_json(const Json& json, Sticker& object)
    {
        VALUE_FROM_JSON(file_id)
        VALUE_FROM_JSON(file_unique_id)
        VALUE_FROM_JSON(type)
        VALUE_FROM_JSON(width)
        VALUE_FROM_JSON(height)
        VALUE_FROM_JSON(is_animated)
        VALUE_FROM_JSON(is_video)
        OBJECT_FROM_JSON(thumb)
        VALUE_FROM_JSON(emoji)
        VALUE_FROM_JSON(set_name)
        OBJECT_FROM_JSON(premium_animation)
        OBJECT_FROM_JSON(mask_position)
        VALUE_FROM_JSON(custom_emoji_id)
        VALUE_FROM_JSON(file_size)
    }
}

#endif