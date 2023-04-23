#include "MyBot.h"

const std::string MyBot::MyBot::LOG_CONFIG_PATH = "LogConfig.xml";
const std::string MyBot::MyBot::OPENAI_USER = "Telegram_bot";

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

    _bot->Start();
}

void MyBot::MyBot::Log(const Telebot::Message::Ptr& message)
{
    std::string logMessage = "user: " + std::to_string(message->from->id) + ", text:" + message->text;
    _logger->Info(logMessage);
}

void MyBot::MyBot::Echo(const Telebot::Message::Ptr& message)
{
    _bot->SendMessageAsync(message->from->id, message->text);
}

void MyBot::MyBot::GptSession(const Telebot::Message::Ptr& message)
{
    std::int64_t id = message->from->id;
    if (_chatGptSessions.find(id) == _chatGptSessions.end())
    {
        OpenAI::ChatGpt::Ptr chatGpt = _openAI->StartChatGptSession(OPENAI_USER, std::to_string(id));
        _chatGptSessions.insert(std::make_pair(id, chatGpt));
    }
    std::string answer = _chatGptSessions[id]->Chat("Hi");
    _bot->SendMessageAsync(id, answer);
}

void MyBot::MyBot::Chat(const Telebot::Message::Ptr& message)
{
    std::int64_t id = message->from->id;
    if (_chatGptSessions.find(id) != _chatGptSessions.end())
    {
        std::string answer = _chatGptSessions[id]->Chat(message->text);
        _bot->SendMessageAsync(id, answer);
    }
}