#ifndef Telebot_InputVenueMessageContentH
#define Telebot_InputVenueMessageContentH

#include "InputMessageContent.h"

namespace Telebot
{
    class InputVenueMessageContent : public InputMessageContent
    {
    public:
        typedef std::shared_ptr<InputVenueMessageContent> Ptr;

        static const std::string TYPE;

        InputVenueMessageContent()
        {
            Type = TYPE;
        }

        float Latitude;
        float Longitude;
        std::string Title;
        std::string Address;
        std::string FoursquareId;
        std::string FoursquareType;
        std::string GooglePlaceId;
        std::string GooglePlaceType;
    };
}

#endif