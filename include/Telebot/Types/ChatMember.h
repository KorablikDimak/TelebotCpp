#ifndef Telebot_ChatMemberH
#define Telebot_ChatMemberH

#include "User.h"

namespace Telebot
{
    class ChatMember
    {
    public:
        typedef std::shared_ptr<ChatMember> Ptr;

        ChatMember() = default;
        virtual ~ChatMember() = default;

        std::string status;
        User::Ptr user;
    };

    inline void from_json(const Json& json, ChatMember& object)
    {
        VALUE_FROM_JSON(status)
        OBJECT_FROM_JSON(user)
    }
}

#endif