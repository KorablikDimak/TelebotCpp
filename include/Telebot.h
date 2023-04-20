#ifndef Telebot_BotH
#define Telebot_BotH

#include "Telebot/CancellationTokenSource.h"
#include "Telebot/Api.h"
#include "Telebot/Event.h"
#include "Telebot/MethodHandler.h"
#include "Telebot/StaticMethodHandler.h"

typedef std::shared_ptr<Telebot::Event<const Telebot::Message::Ptr&>> MessageEvent;

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

        std::future<Message::Ptr> SendMessageAsync(std::int64_t chatId, const std::string& text);
        std::future<bool> SetCommandAsync(const std::string& command, const std::string& description);
        std::future<bool> SetCommandAsync(const BotCommand::Ptr& command);
        std::future<bool> SetCommandsAsync(const std::vector<BotCommand::Ptr>& commands);

    private:
        MessageEvent _onAnyMessage;
        std::map<std::string, MessageEvent> _onMessage;
        std::map<std::string, MessageEvent> _onCommand;

    public:
        MessageEvent OnAnyMessage();
        MessageEvent OnMessage(const std::string& message);
        MessageEvent OnCommand(const std::string& command);
    };
}

#endif