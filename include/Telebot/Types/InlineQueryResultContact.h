#ifndef Telebot_InlineQueryResultContactH
#define Telebot_InlineQueryResultContactH

#include "InlineQueryResult.h"
#include "InputMessageContent.h"

namespace Telebot
{
    class InlineQueryResultContact : public InlineQueryResult
    {
    public:
        typedef std::shared_ptr<InlineQueryResultContact> Ptr;

        static const std::string TYPE;

        InlineQueryResultContact()
        {
            Type = TYPE;
        }

        std::string PhoneNumber;
        std::string FirstName;
        std::string LastName;
        std::string Vcard;
        InputMessageContent::Ptr InputMessageContent;
        std::string ThumbUrl;
        std::int32_t ThumbWidth;
        std::int32_t ThumbHeight;
    };
}

#endif