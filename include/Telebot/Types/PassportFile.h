#ifndef Telebot_PassportFileH
#define Telebot_PassportFileH

#include "Common/JsonMacros.h"

namespace Telebot
{
    class PassportFile
    {
    public:
        typedef std::shared_ptr<PassportFile> Ptr;

        std::string file_id;
        std::string file_unique_id;
        std::int32_t file_size;
        std::int32_t file_date;
    };

    inline void from_json(const Json& json, PassportFile& object)
    {
        VALUE_FROM_JSON(file_id)
        VALUE_FROM_JSON(file_unique_id)
        VALUE_FROM_JSON(file_size)
        VALUE_FROM_JSON(file_date)
    }
}

#endif