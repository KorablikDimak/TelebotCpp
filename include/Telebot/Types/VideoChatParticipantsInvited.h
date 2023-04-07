#ifndef Telebot_VideoChatParticipantsInvitedH
#define Telebot_VideoChatParticipantsInvitedH

#include "User.h"

namespace Telebot
{
    class VideoChatParticipantsInvited
    {
    public:
        typedef std::shared_ptr<VideoChatParticipantsInvited> Ptr;

        std::vector<User::Ptr> users;
    };

    inline void from_json(const Json& json, VideoChatParticipantsInvited& object)
    {
        OBJECTS_FROM_JSON(users)
    }
}

#endif