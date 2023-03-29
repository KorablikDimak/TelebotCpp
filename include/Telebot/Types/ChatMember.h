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

        std::string Status;
        User::Ptr User;
    };
}

#endif