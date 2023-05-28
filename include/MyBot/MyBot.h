#ifndef MyBot_MyBotH
#define MyBot_MyBotH

#include "Environment.h"
#include "Telebot.h"
#include "OpenAI.h"
#include "DbCash.h"
#include "Common/MethodHandler.h"
#include "CInfoLog.h"

namespace MyBot
{
    typedef Telebot::InlineKeyboardButton::Ptr InlineButton;
    typedef Telebot::Message::Ptr Message;
    typedef Telebot::CallbackQuery::Ptr Callback;

    class MyBot
    {
    private:
        static const std::string FILE_DIRECTORY;
        static const std::string OPENAI_USER;
        static const unsigned short REQUESTS_PER_MINUTE_LIMIT;

        std::unique_ptr<Telebot::Telebot> _bot;
        std::unique_ptr<OpenAI::OpenAI> _openAI;
        DbRequest::Ptr _dbRequest;
        std::unique_ptr<DbCash> _dbCash;
        Environment::Ptr _environment;
        std::atomic<unsigned short> _requestsPerLastMinute;
        std::unique_ptr<Common::CancellationTokenSource> _cancellationTokenSource;
        std::map<std::int64_t, OpenAI::OpenAIModel::Ptr> _openAiSessions;
        CInfoLog::Logger::Ptr _logger;

        #define LEXICAL_ITEM(token) \
        _environment->GetLexicalItem(_dbCash->GetUserCash(id)->language, token)

        void Accept();

    public:
        typedef std::shared_ptr<MyBot> Ptr;

        explicit MyBot(const std::map<std::string, std::string>& args);
        ~MyBot();

        void Start();
        void StartAsync();
        void Stop();

        void SetLogger(const std::string& logConfigPath);

        void StartCommand(const Message& message);
        void GptSession(const Message& message);
        void WhisperSession(const Message& message);
        void DalleSession(const Message& message);
        void GetUsageInfo(const Message& message);
        void GetPayment(const Message& message);
        void GetHelp(const Message& message);
        void SetSettings(const Message& message);

        void GetGptHelp(const Callback& callback);
        void GetWhisperHelp(const Callback& callback);
        void GetDalleHelp(const Callback& callback);
        void SetGptSettings(const Callback& callback);
        void SetWhisperSettings(const Callback& callback);
        void SetDalleSettings(const Callback& callback);
        void SetLanguage(const Callback& callback);
        void BackSettings(const Callback& callback);
        void SetContextSize(const Callback& callback);
        void SetGptTemperature(const Callback& callback);
        void SetGptAllowVoice(const Callback& callback);
        void SetWhisperTemperature(const Callback& callback);
        void SetDalleSize(const Callback& callback);
        void SetDalleAllowVoice(const Callback& callback);
        void SetEnglish(const Callback& callback);
        void SetRussian(const Callback& callback);

        void Chat(const Message& message);
        void Transcript(const Message& message);
        void CreateImage(const Message& message);

    private:
        void ConvertAudio(const std::string& filePath);
        bool UserHasTokens(std::int64_t userId);

        void SetContextSizeValue(const Callback& callback, unsigned char contextSize);
        void SetGptTemperatureValue(const Callback& callback, float temperature);
        void SetGptAllowVoiceValue(const Callback& callback, bool allowVoice);
        void SetWhisperTemperatureValue(const Callback& callback, float temperature);
        void SetDalleSizeValue(const Callback& callback, Size size);
        void SetDalleAllowVoiceValue(const Callback& callback, bool allowVoice);

        template<typename TResult>
        std::future<TResult> AddToQueue(std::function<TResult(const OpenAI::OpenAIModel::Ptr&,
                                                              const Message&)> task,
                                        const OpenAI::OpenAIModel::Ptr& model,
                                        const Message& message)
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

        std::list<std::future<Message>> _telebotThreads;
        std::mutex _telebotThreadsMutex;
        std::future<void> _telebotThreadsChecker;

        std::list<std::future<bool>> _dbThreads;
        std::mutex _dbThreadsMutex;
        std::future<void> _dbThreadsChecker;

        std::list<std::future<void>> _commonThreads;
        std::mutex _commonMutex;
        std::future<void> _commonChecker;

        #define OPENAI_TASK(future)\
        { \
            std::unique_lock<std::mutex> lock(_openAiThreadsMutex); \
            _openAiThreads.push_back(std::move(future)); \
            lock.unlock(); \
        }

        #define TELEBOT_TASK(future)\
        { \
            std::unique_lock<std::mutex> lock(_telebotThreadsMutex); \
            _telebotThreads.push_back(std::move(future)); \
            lock.unlock(); \
        }

        #define DB_TASK(future)\
        { \
            std::unique_lock<std::mutex> lock(_dbThreadsMutex); \
            _dbThreads.push_back(std::move(future)); \
            lock.unlock(); \
        }

        #define COMMON_TASK(future) \
        { \
            std::unique_lock<std::mutex> lock(_commonMutex); \
            _commonThreads.push_back(std::move(future)); \
            lock.unlock(); \
        }

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