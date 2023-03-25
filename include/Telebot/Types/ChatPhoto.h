#ifndef TelebotT_ChatPhotoH
#define Telebot_ChatPhotoH

#include <memory>
#include <string>

namespace Telebot
{
    class ChatPhoto
    {
    public:
        typedef std::shared_ptr<ChatPhoto> Ptr;

        std::string SmallFileId;
        std::string SmallFileUniqueId;
        std::string BigFileId;
        std::string BigFileUniqueId;
    };
}

#endif