#include "Telebot/Bot.h"

Telebot::Bot::Bot(const std::string &token)
{
    _api = std::make_unique<Api>(token);
    _isProcess = true;
    User::Ptr user = _api->GetMe();
    if (user->IsBot) Start();
}

Telebot::Bot::~Bot()
{
    _isProcess = false;
}

void Telebot::Bot::Start()
{
    _isProcess = true;
}

void Telebot::Bot::Stop()
{
    _isProcess = false;
}