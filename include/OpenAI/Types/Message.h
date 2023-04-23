#ifndef OpenAI_MessageH
#define OpenAI_MessageH

#include "Common/JsonMacros.h"

namespace OpenAI
{
    class Message
    {
    public:
        typedef std::shared_ptr<Message> Ptr;

        std::string role;
        std::string content;
        std::string name;
    };

    inline void to_json(Json& json, const Message::Ptr& object)
    {
        VALUE_TO_JSON(role)
        VALUE_TO_JSON(content)
        VALUE_TO_JSON(name)
    }
}

#endif