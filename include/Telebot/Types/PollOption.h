#ifndef Telebot_PollOptionH
#define Telebot_PollOptionH

#include <memory>
#include <string>
#include <vector>

namespace Telebot
{
    class PollOption
    {
    public:
        typedef std::shared_ptr<PollOption> Ptr;

        std::string Text;
        std::int64_t VoterCount;
    };
}

#endif