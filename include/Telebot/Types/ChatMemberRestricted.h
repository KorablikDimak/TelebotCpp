#ifndef Telebot_ChatMemberRestrictedH
#define Telebot_ChatMemberRestrictedH

#include "Telebot/Types/ChatMember.h"

namespace Telebot
{
    class ChatMemberRestricted : public ChatMember
    {
    public:
        static const std::string STATUS;

        typedef std::shared_ptr<ChatMemberRestricted> Ptr;

        ChatMemberRestricted()
        {
            Status = STATUS;
        }

        bool IsMember;
        bool CanSendMessages;
        bool CanSendAudios;
        bool CanSendDocuments;
        bool CanSendPhotos;
        bool CanSendVideos;
        bool CanSendVideoNotes;
        bool CanSendVoiceNotes;
        bool CanSendPolls;
        bool CanSendOtherMessages;
        bool CanAddWebPagePreviews;
        bool CanChangeInfo;
        bool CanInviteUsers;
        bool CanPinMessages;
        bool CanManageTopics;
        unsigned int UntilDate;
    };
}

#endif