#ifndef Telebot_InlineQueryResultLocationH
#define Telebot_InlineQueryResultLocationH

#include "InlineQueryResult.h"
#include "InputMessageContent.h"

namespace Telebot
{
    class InlineQueryResultLocation : public InlineQueryResult
    {
    public:
        typedef std::shared_ptr<InlineQueryResultLocation> Ptr;

        static const std::string TYPE;

        InlineQueryResultLocation()
        {
            Type = TYPE;
        }

        float Latitude;
        float Longitude;
        std::string Title;
        float HorizontalAccuracy;
        std::int32_t LivePeriod;
        std::int32_t Heading;
        std::int32_t ProximityAlertRadius;
        InputMessageContent::Ptr InputMessageContent;
        std::string ThumbUrl;
        std::int32_t ThumbWidth;
        std::int32_t ThumbHeight;
    };
}

#endif