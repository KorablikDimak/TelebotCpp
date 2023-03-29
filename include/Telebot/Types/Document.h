#ifndef Telebot_DocumentH
#define Telebot_DocumentH

#include "PhotoSize.h"

namespace Telebot
{
    class Document
    {
    public:
        typedef std::shared_ptr<Document> Ptr;

        std::string FileId;
        std::string FileUniqueId;
        PhotoSize::Ptr Thumb;
        std::string FileName;
        std::string MimeType;
        std::int64_t FileSize;
    };
}

#endif