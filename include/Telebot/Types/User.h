#ifndef Telebot_UserH
#define Telebot_UserH

#include "Common/JsonMacros.h"

namespace Telebot
{
    class User
    {
    public:
        typedef std::shared_ptr<User> Ptr;

        std::int64_t id;
        bool is_bot;
        std::string first_name;
        std::string last_name;
        std::string username;
        std::string language_code;
        bool is_premium;
        bool added_to_attachment_menu;
        bool can_join_groups;
        bool can_read_all_group_messages;
        bool supports_inline_queries;
    };

    inline void from_json(const Json& json, User& object)
    {
        VALUE_FROM_JSON(id)
        VALUE_FROM_JSON(is_bot)
        VALUE_FROM_JSON(first_name)
        VALUE_FROM_JSON(last_name)
        VALUE_FROM_JSON(username)
        VALUE_FROM_JSON(language_code)
        VALUE_FROM_JSON(is_premium)
        VALUE_FROM_JSON(added_to_attachment_menu)
        VALUE_FROM_JSON(can_join_groups)
        VALUE_FROM_JSON(can_read_all_group_messages)
        VALUE_FROM_JSON(supports_inline_queries)
    }
}

#endif