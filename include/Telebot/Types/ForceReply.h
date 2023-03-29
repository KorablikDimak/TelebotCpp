#ifndef Telebot_ForceReplyH
#define Telebot_ForceReplyH

#include "GenericReply.h"

namespace Telebot
{
    class ForceReply : public GenericReply
    {
    public:
        typedef std::shared_ptr<ForceReply> Ptr;

        bool ForceReply;
        std::string InputFieldPlaceholder;
        bool Selective;
    };
}

#endif