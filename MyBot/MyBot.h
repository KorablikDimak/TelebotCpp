#ifndef MyBot_MyBotH
#define MyBot_MyBotH

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
        ~MyBot();

        void GptSession(const Telebot::Message::Ptr& message);
        void Chat(const Telebot::Message::Ptr& message);

    private:
        std::unique_ptr<Common::CancellationTokenSource> _queueControllerTokenSource;

        static const unsigned short REQUESTS_PER_MINUTE_LIMIT;
        std::queue<std::pair<OpenAI::GptModel::Ptr, Telebot::Message::Ptr>> _requestQueue;
        std::mutex _queueControllerMutex;
        std::future<void> _queueController;
        void ControlQueue();

        std::list<std::future<bool>> _queueThreads;
        std::mutex _queueThreadsMutex;
        std::future<void> _queueThreadsChecker;

        std::list<std::future<Telebot::Message::Ptr>> _telebotThreads;
        std::mutex _telebotThreadsMutex;
        std::future<void> _telebotThreadsChecker;

        template<typename T>
        void CheckThreads(std::list<std::future<T>>& threads, std::mutex& mutex)
        {
            while (!_queueControllerTokenSource->Token()->IsCancellationRequested())
            {
                std::unique_lock<std::mutex> lock(mutex);
                std::list<std::future<T>> newThreads;
                for (auto& thread : threads)
                    if (!thread.valid()) newThreads.push_back(std::move(thread));
                threads.swap(newThreads);
                lock.unlock();
                std::this_thread::sleep_for(std::chrono::seconds(10));
            }
        }
    };
}

#endif