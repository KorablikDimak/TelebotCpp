#ifndef Telebot_PollOptionH
#define Telebot_PollOptionH

#include <json.hpp>

typedef nlohmann::json Json;

namespace Telebot
{
    class PollOption
    {
    public:
        typedef std::shared_ptr<PollOption> Ptr;

        std::string text;
        std::int64_t voter_count;
    };

    inline void from_json(const Json& json, PollOption& object)
    {
        VALUE_FROM_JSON(text)
        VALUE_FROM_JSON(voter_count)
    }
}

#endif