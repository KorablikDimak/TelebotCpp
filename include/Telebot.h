#ifndef Telebot_TelebotH
#define Telebot_TelebotH

#include "Common/Event.h"
#include "Common/CancellationTokenSource.h"
#include "Telebot/TelebotApi.h"

typedef std::shared_ptr<Common::Event<const Telebot::Message::Ptr&>> MessageEvent;
typedef std::shared_ptr<Common::Event<const Telebot::CallbackQuery::Ptr&>> CallbackQueryEvent;

namespace Telebot
{
    class Telebot
    {
    private:
        std::unique_ptr<TelebotApi> _api;
        std::unique_ptr<Common::CancellationTokenSource> _acceptorTokenSource;
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

        std::future<Message::Ptr> SendMessageAsync(const std::int64_t& chatId, const std::string& text,
                                                   const GenericReply::Ptr& genericReply = nullptr);
        std::future<bool> SetCommandAsync(const std::string& command, const std::string& description);
        std::future<bool> SetCommandAsync(const BotCommand::Ptr& command);
        std::future<bool> SetCommandsAsync(const std::vector<std::pair<std::string, std::string>>& commands);
        std::future<bool> SetCommandsAsync(const std::vector<BotCommand::Ptr>& commands);
        std::future<std::string> DownloadFileAsync(const std::string& fileId, const std::string& toDirectory);
        std::future<Message::Ptr> SendPhotoAsync(const std::int64_t& chatId,
                                                 const boost::variant<std::string, InputFile::Ptr>& url);
        std::future<bool> AnswerCallbackQueryAsync(const std::string& callbackQueryId, const std::string& text = "",
                                                   const bool& showAlert = false);

    private:
        MessageEvent _onAnyMessage;
        std::map<std::string, MessageEvent> _onMessage;
        std::map<std::string, MessageEvent> _onCommand;
        MessageEvent _onVoice;
        CallbackQueryEvent _onAnyCallbackQuery;
        std::map<std::string, CallbackQueryEvent> _onCallbackQuery;

    public:
        MessageEvent OnAnyMessage();
        MessageEvent OnMessage(const std::string& message);
        MessageEvent OnCommand(const std::string& command);
        MessageEvent OnVoice();
        CallbackQueryEvent OnAnyCallbackQuery();
        CallbackQueryEvent OnCallbackQuery(const std::string& callback_data);
    };
}

#endif