#ifndef Telebot_KeyboardButtonRequestChatH
#define Telebot_KeyboardButtonRequestChatH

#include "ChatAdministratorRights.h"

namespace Telebot
{
    class KeyboardButtonRequestChat
    {
    public:
        typedef std::shared_ptr<KeyboardButtonRequestChat> Ptr;

        std::int32_t RequestId;
        bool ChatIsChannel;
        bool ChatIsForum;
        bool ChatHasUsername;
        bool ChatIsCreated;
        ChatAdministratorRights::Ptr UserAdministratorRights;
        bool BotIsMember;
    };
}

#endif