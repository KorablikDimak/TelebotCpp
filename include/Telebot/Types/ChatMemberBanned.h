#ifndef Telebot_ChatMemberBannedH
#define Telebot_ChatMemberBannedH

#include "ChatMember.h"

namespace Telebot
{
    class ChatMemberBanned : public ChatMember
    {
    public:
        typedef std::shared_ptr<ChatMemberBanned> Ptr;

        static const std::string STATUS;

        ChatMemberBanned()
        {
            Status = STATUS;
        }

        std::int32_t UntilDate;
    };
}

#endif