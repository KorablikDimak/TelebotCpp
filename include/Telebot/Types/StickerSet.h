#ifndef Telebot_StickerSetH
#define Telebot_StickerSetH

#include <vector>

#include "Sticker.h"
#include "PhotoSize.h"

namespace Telebot
{
    class StickerSet
    {
    public:
        typedef std::shared_ptr<StickerSet> Ptr;

        enum class Type
        {
            Regular, Mask, CustomEmoji
        };

        std::string Name;
        std::string Title;
        Type Type;
        bool IsAnimated;
        bool IsVideo;
        std::vector<Sticker::Ptr> Stickers;
        PhotoSize::Ptr Thumb;
    };
}

#endif