#ifndef Telebot_BotCommandScopeChatMemberH
#define Telebot_BotCommandScopeChatMemberH

#include "BotCommandScope.h"

namespace Telebot
{
    class BotCommandScopeChatMember : public BotCommandScope
    {
    public:
        typedef std::shared_ptr<BotCommandScopeChatMember> Ptr;

        static const std::string TYPE;

        BotCommandScopeChatMember()
        {
            type = TYPE;
        }

        std::int64_t ChatId;
        std::int64_t UserId;
    };
}

#endif