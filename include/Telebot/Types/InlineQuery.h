#ifndef Telebot_InlineQueryH
#define Telebot_InlineQueryH

#include "User.h"
#include "Location.h"

namespace Telebot
{
    class InlineQuery
    {
    public:
        typedef std::shared_ptr<InlineQuery> Ptr;

        std::string id;
        User::Ptr from;
        std::string query;
        std::string offset;
        std::string chat_type;
        Location::Ptr location;
    };

    void from_json(const Json& json, InlineQuery& object)
    {
        VALUE_FROM_JSON(id)
        OBJECT_FROM_JSON(from)
        VALUE_FROM_JSON(query)
        VALUE_FROM_JSON(offset)
        VALUE_FROM_JSON(chat_type)
        OBJECT_FROM_JSON(location)
    }
}

#endif