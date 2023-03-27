#ifndef Telebot_ChatAdministratorRightsH
#define Telebot_ChatAdministratorRightsH

#include <memory>

namespace Telebot
{
    class ChatAdministratorRights
    {
    public:
        typedef std::shared_ptr<ChatAdministratorRights> Ptr;

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
    };
}

#endif