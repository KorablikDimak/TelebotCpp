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

        std::string fileId;
        std::string fileUniqueId;
        int width;
        int height;
        int fileSize;
    };
}

#endif