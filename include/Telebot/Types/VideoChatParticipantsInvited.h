#ifndef Telebot_VideoChatParticipantsInvitedH
#define Telebot_VideoChatParticipantsInvitedH

#include "Telebot/Types/User.h"

namespace Telebot
{
    class VideoChatParticipantsInvited
    {
    public:
        typedef std::shared_ptr<VideoChatParticipantsInvited> Ptr;

        std::vector<User::Ptr> Users;
    };
}

#endif