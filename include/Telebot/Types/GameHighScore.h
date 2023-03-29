#ifndef Telebot_GameHighScoreH
#define Telebot_GameHighScoreH

#include "PhotoSize.h"
#include "User.h"

namespace Telebot
{
    class GameHighScore
    {
    public:
        typedef std::shared_ptr<GameHighScore> Ptr;

        std::string Position;
        User::Ptr User;
        std::int32_t Score;
    };
}

#endif