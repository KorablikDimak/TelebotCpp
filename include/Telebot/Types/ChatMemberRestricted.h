#ifndef Telebot_ChatMemberRestrictedH
#define Telebot_ChatMemberRestrictedH

#include "ChatMember.h"

namespace Telebot
{
    class ChatMemberRestricted : public ChatMember
    {
    public:
        typedef std::shared_ptr<ChatMemberRestricted> Ptr;

        static const std::string STATUS;

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
        std::uint32_t UntilDate;
    };
}

#endif