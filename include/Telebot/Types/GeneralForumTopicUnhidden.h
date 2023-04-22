#ifndef Telebot_GeneralForumTopicUnhiddenH
#define Telebot_GeneralForumTopicUnhiddenH

#include "Common/JsonMacros.h"

namespace Telebot
{
    class GeneralForumTopicUnhidden
    {
    public:
        typedef std::shared_ptr<GeneralForumTopicUnhidden> Ptr;
    };

    inline void from_json(const Json& json, GeneralForumTopicUnhidden& object) {}
}

#endif