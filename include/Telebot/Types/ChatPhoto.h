#ifndef Telebot_ChatPhotoH
#define Telebot_ChatPhotoH

#include "Common/JsonMacros.h"

namespace Telebot
{
    class ChatPhoto
    {
    public:
        typedef std::shared_ptr<ChatPhoto> Ptr;

        std::string small_file_id;
        std::string small_file_unique_id;
        std::string big_file_id;
        std::string big_file_unique_id;
    };

    inline void from_json(const Json& json, ChatPhoto& object)
    {
        VALUE_FROM_JSON(small_file_id)
        VALUE_FROM_JSON(small_file_unique_id)
        VALUE_FROM_JSON(big_file_id)
        VALUE_FROM_JSON(big_file_unique_id)
    }
}

#endif