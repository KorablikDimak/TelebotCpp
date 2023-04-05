#include "Telebot.h"

Telebot::Telebot::Telebot(const std::string &token)
{
    _api = std::make_unique<Api>(token);
    _isProcess = true;
    User::Ptr user = _api->GetMe();
    if (user->IsBot) Start();
}

Telebot::Telebot::~Telebot()
{
    Stop();
}

void Telebot::Telebot::Start()
{
    _isProcess = true;
}

void Telebot::Telebot::Stop()
{
    _isProcess = false;
}