#include "MyBot.h"

const std::string MyBot::MyBot::LOG_CONFIG_PATH = "LogConfig.xml";
const std::string MyBot::MyBot::OPENAI_USER = "TelegramBot";

MyBot::MyBot::MyBot(const std::string& botToken, const std::string& openAIToken)
{
    _bot = std::make_unique<Telebot::Telebot>(botToken);
    _openAI = std::make_unique<OpenAI::OpenAI>(openAIToken);

    auto factory = CInfoLog::LoggerFactory(LOG_CONFIG_PATH);
    _logger = factory.CreateLogger();

    auto setCommandGptResult = _bot->SetCommandAsync("gpt", "start chat gpt session");
    if (!setCommandGptResult.get()) throw std::runtime_error("set command failed");

    *_bot->OnCommand("gpt") += THIS_METHOD_HANDLER(&MyBot::GptSession)
    *_bot->OnAnyMessage() += THIS_METHOD_HANDLER(&MyBot::Chat)

    _queueControllerTokenSource = std::make_unique<Common::CancellationTokenSource>();
    _queueController = std::async(std::launch::async, [this](){ ControlQueue(); });
    _queueThreadsChecker = std::async(std::launch::async, [this](){ CheckThreads(_queueThreads, _queueThreadsMutex); });
    _telebotThreadsChecker = std::async(std::launch::async, [this](){ CheckThreads(_telebotThreads, _telebotThreadsMutex); });

    _bot->Start();
}

MyBot::MyBot::~MyBot()
{
    _queueControllerTokenSource->Cancel();

    std::unique_lock<std::mutex> queueLock(_queueThreadsMutex);
    for (auto& task : _queueThreads) task.get();
    queueLock.unlock();
    _queueThreadsChecker.wait();

    std::unique_lock<std::mutex> telebotLock(_telebotThreadsMutex);
    for (auto& task : _telebotThreads) task.get();
    telebotLock.unlock();
    _telebotThreadsChecker.wait();

    _queueController.wait();
}

void MyBot::MyBot::GptSession(const Telebot::Message::Ptr& message)
{
    std::int64_t id = message->from->id;
    if (_gptTurboSessions.find(id) == _gptTurboSessions.end())
    {
        OpenAI::GptModel::Ptr chatGpt = _openAI->GptTurboSession(std::to_string(id), OPENAI_USER, OpenAI::Role::User);
        _gptTurboSessions.insert(std::make_pair(id, chatGpt));
    }

    auto onSend = _bot->SendMessageAsync(id, "Hello! How can I assist you today?");

    std::unique_lock<std::mutex> telebotLock(_telebotThreadsMutex);
    _telebotThreads.push_back(std::move(onSend));
    telebotLock.unlock();
}

void MyBot::MyBot::Chat(const Telebot::Message::Ptr& message)
{
    std::int64_t id = message->from->id;
    if (_gptTurboSessions.find(id) != _gptTurboSessions.end())
    {
        std::unique_lock<std::mutex> lock(_queueControllerMutex);
        _requestQueue.push(std::make_pair(_gptTurboSessions[id], message));
        lock.unlock();
    }
}

const unsigned short MyBot::MyBot::REQUESTS_PER_MINUTE_LIMIT = 3;

void MyBot::MyBot::ControlQueue()
{
    std::shared_ptr<std::atomic<unsigned short>> requestsPerLastMinute = std::make_shared<std::atomic<unsigned short>>(0);

    while (!_queueControllerTokenSource->Token()->IsCancellationRequested())
    {
        if (*requestsPerLastMinute >= REQUESTS_PER_MINUTE_LIMIT || _requestQueue.empty())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        };

        std::future<bool> queue = std::async(std::launch::async, [this, requestsPerLastMinute]() -> bool
        {
            std::unique_lock<std::mutex> queueLock(_queueControllerMutex);
            if (*requestsPerLastMinute >= REQUESTS_PER_MINUTE_LIMIT || _requestQueue.empty()) return true;
            ++(*requestsPerLastMinute);
            OpenAI::GptModel::Ptr gptModel = _requestQueue.front().first;
            Telebot::Message::Ptr message = _requestQueue.front().second;
            _requestQueue.pop();
            queueLock.unlock();

            std::int64_t id = message->from->id;

            std::string logMessage = "user: " + std::to_string(id) + " to gpt, prompt: " + message->text;
            _logger->Trace(logMessage);

            std::string answer = gptModel->Chat(message->text);

            std::thread timer([requestsPerLastMinute]()
            {
                std::this_thread::sleep_for(std::chrono::seconds(60));
                if (*requestsPerLastMinute > 0) --(*requestsPerLastMinute);
            });
            timer.detach();

            logMessage = "gpt to user: " + std::to_string(id) + ", answer: " + answer;
            _logger->Trace(logMessage);

            auto onSend = _bot->SendMessageAsync(id, answer);

            std::unique_lock<std::mutex> telebotLock(_telebotThreadsMutex);
            _telebotThreads.push_back(std::move(onSend));
            telebotLock.unlock();

            return true;
        });

        std::unique_lock<std::mutex> queueLock(_queueThreadsMutex);
        _queueThreads.push_back(std::move(queue));
        queueLock.unlock();
    }
}