#ifndef Telebot_InputLocationMessageContentH
#define Telebot_InputLocationMessageContentH

#include "InputMessageContent.h"

namespace Telebot
{
    class InputLocationMessageContent : public InputMessageContent
    {
    public:
        typedef std::shared_ptr<InputLocationMessageContent> Ptr;

        static const std::string TYPE;

        InputLocationMessageContent()
        {
            Type = TYPE;
        }

        float Latitude;
        float Longitude;
        float HorizontalAccuracy;
        std::int32_t LivePeriod;
        std::int32_t Heading;
        std::int32_t ProximityAlertRadius;
    };
}

#endif