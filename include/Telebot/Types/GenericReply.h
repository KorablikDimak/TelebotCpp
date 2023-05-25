#ifndef Telebot_GenericReplyH
#define Telebot_GenericReplyH

#include "Common/JsonMacros.h"

namespace Telebot
{
    class GenericReply
    {
    public:
        typedef std::shared_ptr<GenericReply> Ptr;

        virtual ~GenericReply() = default;

        virtual void ToJson(Json& json, const GenericReply::Ptr& object);
    };

    inline void to_json(Json& json, const GenericReply::Ptr& object)
    {
        object->ToJson(json, object);
    }
}

#endif