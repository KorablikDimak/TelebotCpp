#ifndef Telebot_ChatMemberMemberH
#define Telebot_ChatMemberMemberH

#include "Telebot/Types/ChatMember.h"

#include <memory>

namespace Telebot
{
    class ChatMemberMember : public ChatMember
    {
    public:
        static const std::string STATUS;

        typedef std::shared_ptr<ChatMemberMember> Ptr;

        ChatMemberMember()
        {
            Status = STATUS;
        }
    };
}

#endif