#ifndef Telebot_InlineQueryH
#define Telebot_InlineQueryH

#include "Telebot/Types/User.h"
#include "Telebot/Types/Location.h"

namespace Telebot
{
    class InlineQuery
    {
    public:
        typedef std::shared_ptr<InlineQuery> Ptr;

        std::string Id;
        User::Ptr From;
        std::string Query;
        std::string Offset;
        std::string ChatType;
        Location::Ptr Location;
    };
}

#endif