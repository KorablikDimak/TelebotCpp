#ifndef Telebot_CallbackGameH
#define Telebot_CallbackGameH

#include "Common/JsonMacros.h"

namespace Telebot
{
    class CallbackGame
    {
    public:
        typedef std::shared_ptr<CallbackGame> Ptr;
    };

    inline void from_json(const Json& json, CallbackGame& object) {}
    inline void to_json(Json& json, const CallbackGame::Ptr& object) {}
}

#endif