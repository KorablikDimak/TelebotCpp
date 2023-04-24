#ifndef MyBot_MyBotH
#define MyBot_MyBotH

#include <queue>
#include <functional>
#include <chrono>

#include "Telebot.h"
#include "OpenAI.h"
#include "Common/MethodHandler.h"
#include "CInfoLog.h"

namespace MyBot
{
    class MyBot
    {
    private:
        std::unique_ptr<Telebot::Telebot> _bot;
        std::unique_ptr<OpenAI::OpenAI> _openAI;

        static const std::string LOG_CONFIG_PATH;
        CInfoLog::Logger::Ptr _logger;

        static const std::string OPENAI_USER;
        std::map<std::int64_t, OpenAI::GptModel::Ptr> _gptTurboSessions;

    public:
        typedef std::shared_ptr<MyBot> Ptr;

        explicit MyBot(const std::string& botToken, const std::string& openAIToken);
        ~MyBot() = default;

        void GptSession(const Telebot::Message::Ptr& message);
        void Chat(const Telebot::Message::Ptr& message);

    private:
        static const unsigned short REQUESTS_PER_MINUTE_LIMIT;
        std::atomic<unsigned short> _requestsPerLastMinute;
        std::queue<std::pair<OpenAI::GptModel::Ptr, Telebot::Message::Ptr>> _requestQueue;
        std::mutex _queueControllerMutex;
        std::thread _queueController;
        std::unique_ptr<Common::CancellationTokenSource> _queueControllerTokenSource;
        void ControlQueue();
    };
}

#endif