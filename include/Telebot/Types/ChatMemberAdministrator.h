#ifndef Telebot_ChatMemberAdministratorH
#define Telebot_ChatMemberAdministratorH

#include "Telebot/Types/ChatMember.h"

namespace Telebot
{
    class ChatMemberAdministrator : public ChatMember
    {
    public:
        static const std::string STATUS;

        typedef std::shared_ptr<ChatMemberAdministrator> Ptr;

        ChatMemberAdministrator()
        {
            Status = STATUS;
        }

        bool CanBeEdited;
        bool IsAnonymous;
        bool CanManageChat;
        bool CanDeleteMessages;
        bool CanManageVideoChats;
        bool CanRestrictMembers;
        bool CanPromoteMembers;
        bool CanChangeInfo;
        bool CanInviteUsers;
        bool CanPostMessages;
        bool CanEditMessages;
        bool CanPinMessages;
        bool CanManageTopics;
        std::string CustomTitle;
    };
}

#endif