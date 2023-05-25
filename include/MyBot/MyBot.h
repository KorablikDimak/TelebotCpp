#ifndef MyBot_MyBotH
#define MyBot_MyBotH

#include "Environment.h"
#include "Telebot.h"
#include "OpenAI.h"
#include "Db/DbConnection.h"
#include "Common/MethodHandler.h"
#include "CInfoLog.h"

namespace MyBot
{
    class MyBot
    {
    private:
        static const std::string FILE_DIRECTORY;
        static const unsigned char POOL_MAX_SIZE;
        static const std::string OPENAI_USER;
        static const unsigned short REQUESTS_PER_MINUTE_LIMIT;

        std::unique_ptr<Telebot::Telebot> _bot;
        std::unique_ptr<OpenAI::OpenAI> _openAI;
        std::unique_ptr<DbProvider::DbConnection> _dbConnection;
        Environment::Ptr _environment;
        std::map<std::int64_t, LanguageCode> _languageCodes;
        std::atomic<unsigned short> _requestsPerLastMinute;
        std::unique_ptr<Common::CancellationTokenSource> _cancellationTokenSource;
        std::map<std::int64_t, OpenAI::OpenAIModel::Ptr> _openAiSessions;
        CInfoLog::Logger::Ptr _logger;

        std::future<bool> IsUser(std::int64_t userId);
        std::future<bool> AddUser(std::int64_t userId);
        std::future<unsigned short> GetRole(std::int64_t userId);
        std::future<bool> SetRole(std::int64_t userId, unsigned short roleId);
        std::future<int> GetUsage(std::int64_t userId);
        std::future<bool> AddUsage(std::int64_t userId, int usage);
        std::future<int> GetUsageLimit(std::int64_t userId);
        std::future<bool> SetUsageLimit(std::int64_t userId, int usageLimit);
        std::future<LanguageCode> GetLanguageCode(std::int64_t userId);
        std::future<bool> SetLanguageCode(std::int64_t userId, LanguageCode languageCode);
        std::future<unsigned short> GetContextLimit(std::int64_t userId);
        std::future<bool> SetContextLimit(std::int64_t userId, unsigned short contextLimit);

        LanguageCode GetLanguageCodeCash(std::int64_t userId);
        void SetLanguageCodeCash(std::int64_t userId, LanguageCode languageCode);

        void Accept();

        #define OPENAI_TASK(future)\
        { \
            std::unique_lock<std::mutex> lock(_openAiThreadsMutex); \
            _openAiThreads.push_back(std::move(future)); \
            lock.unlock(); \
        };

        #define TELEBOT_TASK(future)\
        { \
            std::unique_lock<std::mutex> lock(_telebotThreadsMutex); \
            _telebotThreads.push_back(std::move(future)); \
            lock.unlock(); \
        };

        #define DB_TASK(future)\
        { \
            std::unique_lock<std::mutex> lock(_dbThreadsMutex); \
            _dbThreads.push_back(std::move(future)); \
            lock.unlock(); \
        };

        #define COMMON_TASK(future) \
        { \
            std::unique_lock<std::mutex> lock(_commonMutex); \
            _commonThreads.push_back(std::move(future)); \
            lock.unlock(); \
        };

    public:
        typedef std::shared_ptr<MyBot> Ptr;

        explicit MyBot(const std::map<std::string, std::string>& args);
        ~MyBot();

        void Start();
        void StartAsync();
        void Stop();

        void SetLogger(const std::string& logConfigPath);

        void StartCommand(const Telebot::Message::Ptr& message);
        void GptSession(const Telebot::Message::Ptr& message);
        void WhisperSession(const Telebot::Message::Ptr& message);
        void DalleSession(const Telebot::Message::Ptr& message);
        void GetUsageInfo(const Telebot::Message::Ptr& message);
        void GetPayment(const Telebot::Message::Ptr& message);
        void GetHelp(const Telebot::Message::Ptr& message);
        void SetSettings(const Telebot::Message::Ptr& message);

        void GetGptHelp(const Telebot::CallbackQuery::Ptr& callback);
        void GetWhisperHelp(const Telebot::CallbackQuery::Ptr& callback);
        void GetDalleHelp(const Telebot::CallbackQuery::Ptr& callback);
        void SetGptSettings(const Telebot::CallbackQuery::Ptr& callback);
        void SetWhisperSettings(const Telebot::CallbackQuery::Ptr& callback);
        void SetDalleSettings(const Telebot::CallbackQuery::Ptr& callback);
        void SetLanguage(const Telebot::CallbackQuery::Ptr& callback);

        void Chat(const Telebot::Message::Ptr& message);
        void Transcript(const Telebot::Message::Ptr& message);
        void CreateImage(const Telebot::Message::Ptr& message);

    private:
        void ConvertAudio(const std::string& filePath);
        bool UserHasTokens(std::int64_t userId);

        template<typename TResult>
        std::future<TResult> AddToQueue(std::function<TResult(const OpenAI::OpenAIModel::Ptr&,
                                                              const Telebot::Message::Ptr&)> task,
                                        const OpenAI::OpenAIModel::Ptr& model,
                                        const Telebot::Message::Ptr& message)
        {
            return std::async(std::launch::async, [this, task, model, message]()->TResult
            {
                while (!_cancellationTokenSource->Token()->IsCancellationRequested())
                {
                    if (_requestsPerLastMinute >= REQUESTS_PER_MINUTE_LIMIT)
                    {
                        std::this_thread::sleep_for(std::chrono::milliseconds(100));
                        continue;
                    };

                    ++_requestsPerLastMinute;
                    TResult result = task(model, message);

                    std::thread timer([this]()
                    {
                        std::this_thread::sleep_for(std::chrono::seconds(60));
                        if (_requestsPerLastMinute > 0) --_requestsPerLastMinute;
                    });
                    timer.detach();

                    return result;
                }
            });
        }

        std::list<std::future<bool>> _openAiThreads;
        std::mutex _openAiThreadsMutex;
        std::future<void> _openAiThreadsChecker;

        std::list<std::future<Telebot::Message::Ptr>> _telebotThreads;
        std::mutex _telebotThreadsMutex;
        std::future<void> _telebotThreadsChecker;

        std::list<std::future<bool>> _dbThreads;
        std::mutex _dbThreadsMutex;
        std::future<void> _dbThreadsChecker;

        std::list<std::future<void>> _commonThreads;
        std::mutex _commonMutex;
        std::future<void> _commonChecker;

        template<typename T>
        void CheckThreads(std::list<std::future<T>>& threads, std::mutex& mutex)
        {
            while (!_cancellationTokenSource->Token()->IsCancellationRequested())
            {
                std::unique_lock<std::mutex> lock(mutex);
                std::list<std::future<T>> activeThreads;
                for (auto& thread : threads)
                    if (thread.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout)
                        activeThreads.push_back(std::move(thread));
                threads.swap(activeThreads);
                lock.unlock();
                std::this_thread::sleep_for(std::chrono::seconds(5));
            }
        }
    };
}

#endif