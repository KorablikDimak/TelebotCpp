#ifndef Telebot_ChatPermissionsH
#define Telebot_ChatPermissionsH

#include <memory>

namespace Telebot
{
    class ChatPermissions
    {
    public:
        typedef std::shared_ptr<ChatPermissions> Ptr;

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
    };
}

#endif