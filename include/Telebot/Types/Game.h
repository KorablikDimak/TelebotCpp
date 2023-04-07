#ifndef Telebot_GameH
#define Telebot_GameH

#include "MessageEntity.h"
#include "Animation.h"
#include "PhotoSize.h"

namespace Telebot
{
    class Game
    {
    public:
        typedef std::shared_ptr<Game> Ptr;

        std::string title;
        std::string description;
        std::vector<PhotoSize::Ptr> photo;
        std::string text;
        std::vector<MessageEntity::Ptr> text_entities;
        Animation::Ptr animation;
    };

    inline void from_json(const Json& json, Game& object)
    {
        VALUE_FROM_JSON(title)
        VALUE_FROM_JSON(description)
        OBJECTS_FROM_JSON(photo)
        VALUE_FROM_JSON(text)
        OBJECTS_FROM_JSON(text_entities)
        OBJECT_FROM_JSON(animation)
    }
}

#endif