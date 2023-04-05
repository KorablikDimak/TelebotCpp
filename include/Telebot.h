#ifndef Telebot_BotH
#define Telebot_BotH

#include "Telebot/Api.h"
#include "Telebot/Event.h"
#include "Telebot/MethodHandler.h"
#include "Telebot/StaticMethodHandler.h"

typedef std::map<std::string, std::string> ConfigDictionary;

namespace Telebot
{
    class Telebot
    {
    private:
        std::unique_ptr<Api> _api;
        bool _isProcess;

    public:
        explicit Telebot(const std::string& token);
        ~Telebot();

        void Start();
        void Stop();

        Event<const std::string&> OnMessage;
    };
}

#endif