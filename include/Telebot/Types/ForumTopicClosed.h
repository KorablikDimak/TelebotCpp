#ifndef Telebot_ForumTopicClosedH
#define Telebot_ForumTopicClosedH

#include "Telebot/JsonMacros.h"

namespace Telebot
{
    class ForumTopicClosed
    {
    public:
        typedef std::shared_ptr<ForumTopicClosed> Ptr;
    };

    inline void from_json(const Json& json, ForumTopicClosed& object) {}
}

#endif