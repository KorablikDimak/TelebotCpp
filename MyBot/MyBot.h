#ifndef MyBot_MyBotH
#define MyBot_MyBotH

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
        std::map<std::int64_t, OpenAI::ChatGpt::Ptr> _chatGptSessions;

    public:
        typedef std::shared_ptr<MyBot> Ptr;

        explicit MyBot(const std::string& botToken, const std::string& openAIToken);
        ~MyBot() = default;

        void Log(const Telebot::Message::Ptr& message);
        void Echo(const Telebot::Message::Ptr& message);
        void GptSession(const Telebot::Message::Ptr& message);
        void Chat(const Telebot::Message::Ptr& message);
    };
}

#endif