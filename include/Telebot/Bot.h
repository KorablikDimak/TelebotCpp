#ifndef Telebot_BotH
#define Telebot_BotH

#include <thread>

#include "Api.h"

typedef std::map<std::string, std::string> ConfigDictionary;

namespace Telebot
{
    class Bot
    {
    private:
        std::unique_ptr<Api> _api;
        bool _isProcess;

    public:
        explicit Bot(const std::string& token);
        ~Bot();

        void Start();
        void Stop();
    };
}

#endif