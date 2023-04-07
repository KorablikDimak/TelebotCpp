#ifndef Telebot_DocumentH
#define Telebot_DocumentH

#include "PhotoSize.h"

namespace Telebot
{
    class Document
    {
    public:
        typedef std::shared_ptr<Document> Ptr;

        std::string file_id;
        std::string file_unique_id;
        PhotoSize::Ptr thumb;
        std::string file_name;
        std::string mime_type;
        std::int64_t file_size;
    };

    inline void from_json(const Json& json, Document& object)
    {
        VALUE_FROM_JSON(file_id)
        VALUE_FROM_JSON(file_unique_id)
        OBJECT_FROM_JSON(thumb)
        VALUE_FROM_JSON(file_name)
        VALUE_FROM_JSON(mime_type)
        VALUE_FROM_JSON(file_size)
    }
}

#endif