#ifndef Telebot_DocumentH
#define Telebot_DocumentH

#include "Telebot/Types/PhotoSize.h"

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
        long long FileSize;
    };
}

#endif