#ifndef Telebot_GameH
#define Telebot_GameH

#include "Telebot/Types/MessageEntity.h"
#include "Telebot/Types/Animation.h"
#include "Telebot/Types/PhotoSize.h"

namespace Telebot
{
    class Game
    {
    public:
        typedef std::shared_ptr<Game> Ptr;

        std::string Title;
        std::string Description;
        std::vector<PhotoSize::Ptr> Photo;
        std::string Text;
        std::vector<MessageEntity::Ptr> TextEntities;
        Animation::Ptr Animation;
    };
}

#endif