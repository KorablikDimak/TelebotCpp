#ifndef Telebot_WriteAccessAllowedH
#define Telebot_WriteAccessAllowedH

#include "Telebot/JsonMacros.h"

namespace Telebot
{
    class WriteAccessAllowed
    {
    public:
        typedef std::shared_ptr<WriteAccessAllowed> Ptr;
    };

    inline void from_json(const Json& json, WriteAccessAllowed& object) {}
}

#endif