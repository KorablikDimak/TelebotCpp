#ifndef Telebot_StickerH
#define Telebot_StickerH

#include "Telebot/Types/PhotoSize.h"
#include "Telebot/Types/File.h"
#include "Telebot/Types/MaskPosition.h"

namespace Telebot
{
    class Sticker
    {
    public:
        typedef std::shared_ptr<Sticker> Ptr;

        enum class Type
        {
            Regular, Mask, CustomEmoji
        };

        std::string FileId;
        std::string FileUniqueId;
        Type Type;
        int Width;
        int Height;
        bool IsAnimated;
        bool IsVideo;
        PhotoSize::Ptr Thumb;
        std::string Emoji;
        std::string SetName;
        File::Ptr PremiumAnimation;
        MaskPosition::Ptr MaskPosition;
        std::string CustomEmojiId;
        int FileSize;
    };
}

#endif