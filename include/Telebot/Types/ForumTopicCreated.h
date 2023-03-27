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
        std::int32_t IconColor;
        std::string IconCustomEmojiId;
    };
}

#endif