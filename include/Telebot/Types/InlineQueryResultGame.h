#ifndef Telebot_InlineQueryResultGameH
#define Telebot_InlineQueryResultGameH

#include "InlineQueryResult.h"

namespace Telebot
{
    class InlineQueryResultGame : public InlineQueryResult
    {
    public:
        typedef std::shared_ptr<InlineQueryResultGame> Ptr;

        static const std::string TYPE;

        InlineQueryResultGame()
        {
            Type = TYPE;
        }

        std::string GameShortName;
    };
}

#endif