#ifndef Telebot_BotH
#define Telebot_BotH

#include <thread>

#include "Telebot/CancellationTokenSource.h"
#include "Telebot/Api.h"
#include "Telebot/Event.h"
#include "Telebot/MethodHandler.h"
#include "Telebot/StaticMethodHandler.h"

namespace Telebot
{
    class Telebot
    {
    private:
        std::unique_ptr<Api> _api;
        std::unique_ptr<CancellationTokenSource> _isProcess;

    public:
        explicit Telebot(const std::string& token);
        ~Telebot();

        void Start();
        void Stop();

        Event<const std::string&> OnMessage;
    };
}

#endif