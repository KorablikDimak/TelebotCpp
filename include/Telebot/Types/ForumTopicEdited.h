#ifndef Telebot_ForumTopicEditedH
#define Telebot_ForumTopicEditedH

#include <memory>
#include <string>

namespace Telebot
{
    class ForumTopicEdited
    {
    public:
        typedef std::shared_ptr<ForumTopicEdited> Ptr;

        std::string Name;
        std::string IconCustomEmojiId;
    };
}

#endif