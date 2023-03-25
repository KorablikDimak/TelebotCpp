#ifndef Telebot_ChatMemberOwnerH
#define Telebot_ChatMemberOwnerH

#include "Telebot/Types/ChatMember.h"

namespace Telebot
{
    class ChatMemberOwner : public ChatMember
    {
    public:
        static const std::string STATUS;

        typedef std::shared_ptr<ChatMemberOwner> Ptr;

        ChatMemberOwner()
        {
            Status = STATUS;
        }

        std::string CustomTitle;
        bool IsAnonymous;
    };
}

#endif