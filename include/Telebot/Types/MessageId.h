#ifndef Telebot_MessageIdH
#define Telebot_MessageIdH

#include <memory>

namespace Telebot
{
    class MessageId
    {
    public:
        typedef std::shared_ptr<MessageId> Ptr;

        std::int32_t MessageId;
    };
}

#endif