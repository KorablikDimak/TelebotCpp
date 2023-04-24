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
    _queueController = std::thread([this](){ ControlQueue(); });

    _bot->Start();
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
    _requestsPerLastMinute = 0;

    std::thread timer([this]()
    {
        while (!_queueControllerTokenSource->Token()->IsCancellationRequested())
        {
            std::this_thread::sleep_for(std::chrono::seconds(61));
            _requestsPerLastMinute = 0;
        }
    });

    while (!_queueControllerTokenSource->Token()->IsCancellationRequested())
    {
        if (_requestsPerLastMinute >= REQUESTS_PER_MINUTE_LIMIT || _requestQueue.empty()) continue;

        std::thread queue([this]()
        {
            std::unique_lock<std::mutex> lock(_queueControllerMutex);
            if (_requestsPerLastMinute >= REQUESTS_PER_MINUTE_LIMIT || _requestQueue.empty()) return;
            ++_requestsPerLastMinute;
            OpenAI::GptModel::Ptr gptModel = _requestQueue.front().first;
            Telebot::Message::Ptr message = _requestQueue.front().second;
            _requestQueue.pop();
            lock.unlock();

            std::int64_t id = message->from->id;

            std::string logMessage = "user: " + std::to_string(id) + " to gpt, prompt: " + message->text;
            _logger->Trace(logMessage);

            std::string answer = gptModel->Chat(message->text);

            logMessage = "gpt to user: " + std::to_string(id) + ", answer: " + answer;
            _logger->Trace(logMessage);

            auto onSend = _bot->SendMessageAsync(id, answer);
        });

        queue.detach();
    }
}