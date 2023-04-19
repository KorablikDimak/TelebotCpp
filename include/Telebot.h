#ifndef Telebot_BotH
#define Telebot_BotH

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
        std::unique_ptr<CancellationTokenSource> _cancellationTokenSource;
        std::future<void> _acceptor;

        static const std::int32_t LIMIT;
        std::int32_t _timeout;

        void Accept();

    public:
        explicit Telebot(const std::string& token);
        ~Telebot();

        void Start();
        void StartAsync();
        void Stop();

        void SetTimeout(std::int32_t timeout);

        Event<const Message::Ptr&> OnMessage;
    };
}

#endif