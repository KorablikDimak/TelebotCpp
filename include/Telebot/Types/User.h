#ifndef Telebot_UserH
#define Telebot_UserH

#include <cstdint>
#include <string>
#include <memory>

namespace Telebot
{
    class User
    {
    public:
        typedef std::shared_ptr<User> Ptr;

        long long Id;
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
    };
}

#endif