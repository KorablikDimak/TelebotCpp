#ifndef Telebot_ForumTopicEditedH
#define Telebot_ForumTopicEditedH

#include "Common/JsonMacros.h"

namespace Telebot
{
    class ForumTopicEdited
    {
    public:
        typedef std::shared_ptr<ForumTopicEdited> Ptr;

        std::string name;
        std::string icon_custom_emoji_id;
    };

    inline void from_json(const Json& json, ForumTopicEdited& object)
    {
        VALUE_FROM_JSON(name)
        VALUE_FROM_JSON(icon_custom_emoji_id)
    }
}

#endif