#ifndef Telebot_ControllerH
#define Telebot_ControllerH

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <memory>

#include "Types/Update.h"
#include "Types/User.h"

namespace Telebot
{
    class Api
    {
    public:
        Api() = default;
        ~Api() = default;

        std::vector<Update::Ptr> GetUpdates(int offset = 0, int limit = 100, int timeout = 1,
                                            const std::vector<std::string>& allowedUpdates = std::vector<std::string>());

        User::Ptr GetMe();
    };
}

#endif