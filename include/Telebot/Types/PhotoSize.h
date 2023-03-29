#ifndef Telebot_PhotoSizeH
#define Telebot_PhotoSizeH

#include <string>
#include <memory>

namespace Telebot
{
    class PhotoSize
    {
    public:
        typedef std::shared_ptr<PhotoSize> Ptr;

        std::string FileId;
        std::string FileUniqueId;
        std::int32_t Width;
        std::int32_t Height;
        std::int32_t FileSize;
    };
}

#endif