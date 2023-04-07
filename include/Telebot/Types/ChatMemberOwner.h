#ifndef Telebot_ChatMemberOwnerH
#define Telebot_ChatMemberOwnerH

#include "ChatMember.h"

namespace Telebot
{
    class ChatMemberOwner : public ChatMember
    {
    public:
        typedef std::shared_ptr<ChatMemberOwner> Ptr;

        static const std::string STATUS;

        ChatMemberOwner()
        {
            status = STATUS;
        }

        std::string CustomTitle;
        bool IsAnonymous;
    };
}

#endif