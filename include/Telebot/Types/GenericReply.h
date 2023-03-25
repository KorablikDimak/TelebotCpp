#ifndef Telebot_GenericReplyH
#define Telebot_GenericReplyH

#include <memory>

namespace Telebot
{
    class GenericReply
    {
    public:
        typedef std::shared_ptr<GenericReply> Ptr;

        virtual ~GenericReply() = default;
    };
}

#endif