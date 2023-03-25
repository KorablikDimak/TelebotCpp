#ifndef Telebot_PollH
#define Telebot_PollH

#include "Telebot/Types/PollOption.h"
#include "Telebot/Types/MessageEntity.h"

namespace Telebot
{
class Poll
{
public:
    typedef std::shared_ptr<Poll> Ptr;

    std::string Id;
    std::string Question;
    std::vector<PollOption::Ptr> Options;
    int TotalVoterCount;
    bool IsClosed;
    bool IsAnonymous;
    std::string Type;
    bool AllowsMultipleAnswers;
    int CorrectOptionId;
    std::string Explanation;
    std::vector<MessageEntity::Ptr> ExplanationEntities;
    int OpenPeriod;
    long long CloseDate;
};
}

#endif