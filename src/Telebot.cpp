#include "Telebot.h"

Telebot::Telebot::Telebot(const std::string &token)
{
    _api = std::make_unique<Api>(token);
    User::Ptr user = _api->GetMe();
    if (user->is_bot) Start();
}

Telebot::Telebot::~Telebot()
{
    Stop();
}

void Telebot::Telebot::Start()
{
    _isProcess = std::make_unique<CancellationTokenSource>();
}

void Telebot::Telebot::Stop()
{
    _isProcess->Cancel();
}