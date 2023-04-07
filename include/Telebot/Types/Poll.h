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

        std::string id;
        std::string question;
        std::vector<PollOption::Ptr> options;
        std::int32_t total_voter_count;
        bool is_closed;
        bool is_anonymous;
        std::string type;
        bool allows_multiple_answers;
        std::int32_t correct_optionId;
        std::string explanation;
        std::vector<MessageEntity::Ptr> explanation_entities;
        std::int32_t open_period;
        std::int64_t close_date;
    };

    inline void from_json(const Json& json, Poll& object)
    {
        VALUE_FROM_JSON(id)
        VALUE_FROM_JSON(question)
        OBJECTS_FROM_JSON(options)
        VALUE_FROM_JSON(total_voter_count)
        VALUE_FROM_JSON(is_closed)
        VALUE_FROM_JSON(is_anonymous)
        VALUE_FROM_JSON(type)
        VALUE_FROM_JSON(allows_multiple_answers)
        VALUE_FROM_JSON(correct_optionId)
        VALUE_FROM_JSON(explanation)
        OBJECTS_FROM_JSON(explanation_entities)
        VALUE_FROM_JSON(open_period)
        VALUE_FROM_JSON(close_date)
    }
}

#endif