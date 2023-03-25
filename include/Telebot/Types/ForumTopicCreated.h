#ifndef Telebot_ForumTopicCreatedH
#define Telebot_ForumTopicCreatedH

#include <string>
#include <memory>

namespace Telebot
{
    class ForumTopicCreated
    {
    public:
        typedef std::shared_ptr<ForumTopicCreated> Ptr;

        std::string Name;
        int IconColor;
        std::string IconCustomEmojiId;
    };
}

#endif