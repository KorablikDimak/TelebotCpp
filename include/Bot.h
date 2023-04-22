#ifndef Telebot_TelebotH
#define Telebot_TelebotH

#include "Common/Event.h"
#include "Common/CancellationTokenSource.h"
#include "Telebot/BotApi.h"

typedef std::shared_ptr<Common::Event<const Telebot::Message::Ptr&>> MessageEvent;

namespace Telebot
{
    class Bot
    {
    private:
        std::unique_ptr<BotApi> _api;
        std::unique_ptr<Common::CancellationTokenSource> _cancellationTokenSource;
        std::future<void> _acceptor;

        static const std::int32_t LIMIT;
        std::int32_t _timeout;

        void Accept();

    public:
        explicit Bot(const std::string& token);
        ~Bot();

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