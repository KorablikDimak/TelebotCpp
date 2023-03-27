#ifndef Telebot_BotCommandScopeChatMemberH
#define Telebot_BotCommandScopeChatMemberH

#include "Telebot/Types/BotCommandScope.h"

namespace Telebot
{
    class BotCommandScopeChatMember : public BotCommandScope
    {
    public:
        static const std::string TYPE;

        typedef std::shared_ptr<BotCommandScopeChatMember> Ptr;

        BotCommandScopeChatMember()
        {
            Type = TYPE;
        }

        std::int64_t ChatId;
        std::int64_t UserId;
    };
}

#endif