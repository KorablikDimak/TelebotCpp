#ifndef Telebot_WriteAccessAllowedH
#define Telebot_WriteAccessAllowedH

#include <memory>

namespace Telebot
{
    class WriteAccessAllowed
    {
    public:
        typedef std::shared_ptr<WriteAccessAllowed> Ptr;
    };
}

#endif