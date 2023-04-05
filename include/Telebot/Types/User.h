#ifndef Telebot_UserH
#define Telebot_UserH

#include <string>
#include <memory>
#include <json.hpp>

typedef nlohmann::json Json;

namespace Telebot
{
    class User
    {
    public:
        typedef std::shared_ptr<User> Ptr;

        std::int64_t Id;
        bool IsBot;
        std::string FirstName;
        std::string LastName;
        std::string Username;
        std::string LanguageCode;
        bool IsPremium;
        bool AddedToAttachmentMenu;
        bool CanJoinGroups;
        bool CanReadAllGroupMessages;
        bool SupportsInlineQueries;

        User() = default;

        explicit User(const Json& json)
        {
            Id = json.value<std::int64_t>("id", 0);
            IsBot = json.value<bool>("is_bot", false);
            FirstName = json.value<std::string>("first_name", "");
            LastName = json.value<std::string>("last_name", "");
            Username = json.value<std::string>("username", "");
            LanguageCode = json.value<std::string>("language_code", "");
            IsPremium = json.value<bool>("is_premium", false);
            AddedToAttachmentMenu = json.value<bool>("added_to_attachment_menu", false);
            CanJoinGroups = json.value<bool>("can_join_groups", false);
            CanReadAllGroupMessages = json.value<bool>("can_read_all_group_messages", false);
            SupportsInlineQueries = json.value<bool>("supports_inline_queries", false);
        }

        ~User() = default;
    };
}

#endif