#ifndef Telebot_ForumTopicReopenedH
#define Telebot_ForumTopicReopenedH

#include "Common/JsonMacros.h"

namespace Telebot
{
    class ForumTopicReopened
    {
    public:
        typedef std::shared_ptr<ForumTopicReopened> Ptr;
    };

    inline void from_json(const Json& json, ForumTopicReopened& object) {}
}

#endif