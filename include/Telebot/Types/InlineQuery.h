#ifndef Telebot_InlineQueryH
#define Telebot_InlineQueryH

#include "User.h"
#include "Location.h"

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