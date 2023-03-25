#ifndef Telebot_ChatMemberBannedH
#define Telebot_ChatMemberBannedH

#include "Telebot/Types/ChatMember.h"

namespace Telebot
{
    class ChatMemberBanned : public ChatMember
    {
    public:
        static const std::string STATUS;

        typedef std::shared_ptr<ChatMemberBanned> Ptr;

        ChatMemberBanned()
        {
            Status = STATUS;
        }

        int UntilDate;
    };
}

#endif