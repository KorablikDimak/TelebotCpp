#ifndef Telebot_PollAnswerH
#define Telebot_PollAnswerH

#include "Telebot/Types/User.h"

namespace Telebot
{
    class PollAnswer
    {
    public:
        typedef std::shared_ptr<PollAnswer> Ptr;

        std::string pollId;
        User::Ptr user;
        std::vector<std::int32_t> optionIds;
    };
}

#endif