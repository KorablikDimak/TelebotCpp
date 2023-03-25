#ifndef Telebot_ChatMemberLeftH
#define Telebot_ChatMemberLeftH

#include "Telebot/Types/ChatMember.h"

namespace Telebot
{
    class ChatMemberLeft : public ChatMember
    {
    public:
        static const std::string STATUS;

        typedef std::shared_ptr<ChatMemberLeft> Ptr;

        ChatMemberLeft()
        {
            Status = STATUS;
        }
    };
}

#endif