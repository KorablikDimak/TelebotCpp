#ifndef Telebot_ChatMemberLeftH
#define Telebot_ChatMemberLeftH

#include "ChatMember.h"

namespace Telebot
{
    class ChatMemberLeft : public ChatMember
    {
    public:
        typedef std::shared_ptr<ChatMemberLeft> Ptr;

        static const std::string STATUS;

        ChatMemberLeft()
        {
            status = STATUS;
        }
    };
}

#endif