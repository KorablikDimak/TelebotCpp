#ifndef Telebot_PollH
#define Telebot_PollH

#include "PollOption.h"
#include "MessageEntity.h"

namespace Telebot
{
class Poll
{
public:
    typedef std::shared_ptr<Poll> Ptr;

    std::string Id;
    std::string Question;
    std::vector<PollOption::Ptr> Options;
    std::int32_t TotalVoterCount;
    bool IsClosed;
    bool IsAnonymous;
    std::string Type;
    bool AllowsMultipleAnswers;
    std::int32_t CorrectOptionId;
    std::string Explanation;
    std::vector<MessageEntity::Ptr> ExplanationEntities;
    std::int32_t OpenPeriod;
    std::int64_t CloseDate;
};
}

#endif