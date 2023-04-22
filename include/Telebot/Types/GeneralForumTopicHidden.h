#ifndef Telebot_GeneralForumTopicHiddenH
#define Telebot_GeneralForumTopicHiddenH

#include "Common/JsonMacros.h"

namespace Telebot
{
    class GeneralForumTopicHidden
    {
    public:
        typedef std::shared_ptr<GeneralForumTopicHidden> Ptr;
    };

    inline void from_json(const Json& json, GeneralForumTopicHidden& object) {}
}

#endif