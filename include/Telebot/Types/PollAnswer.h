#ifndef Telebot_PollAnswerH
#define Telebot_PollAnswerH

#include "User.h"

namespace Telebot
{
    class PollAnswer
    {
    public:
        typedef std::shared_ptr<PollAnswer> Ptr;

        std::string PollId;
        User::Ptr User;
        std::vector<std::int32_t> OptionIds;
    };
}

#endif