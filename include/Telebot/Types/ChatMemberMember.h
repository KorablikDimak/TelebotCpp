#ifndef Telebot_ChatMemberMemberH
#define Telebot_ChatMemberMemberH

#include "ChatMember.h"

namespace Telebot
{
    class ChatMemberMember : public ChatMember
    {
    public:
        typedef std::shared_ptr<ChatMemberMember> Ptr;

        static const std::string STATUS;

        ChatMemberMember()
        {
            Status = STATUS;
        }
    };
}

#endif