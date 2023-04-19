#include "Telebot.h"

const std::int32_t Telebot::Telebot::LIMIT = 100;

Telebot::Telebot::Telebot(const std::string &token)
{
    _api = std::make_unique<Api>(token);
    _timeout = 10;
    User::Ptr user = _api->GetMe();
    if (!user->is_bot) throw std::runtime_error("user is not bot");
}

Telebot::Telebot::~Telebot()
{
    Stop();
}

void Telebot::Telebot::Accept()
{
    std::int32_t offset = 0;
    while (!_cancellationTokenSource->Token()->IsCancellationRequested())
    {
        std::vector<std::string> allowedUpdates;
        if (!OnMessage.IsEmpty()) allowedUpdates.emplace_back("message");

        std::vector<Update::Ptr> updates = _api->GetUpdates(offset, LIMIT, _timeout, allowedUpdates);
        if (updates.empty()) continue;

        for (const Update::Ptr& update : updates)
        {
            if (update->message.get() != nullptr) OnMessage(update->message);
        }

        offset = updates[updates.size() - 1]->update_id + 1;
    }
}

void Telebot::Telebot::Start()
{
    if (_cancellationTokenSource == nullptr || _cancellationTokenSource->Token()->IsCancellationRequested())
    {
        _cancellationTokenSource = std::make_unique<CancellationTokenSource>();
        Accept();
    }
}

void Telebot::Telebot::StartAsync()
{
    if (_cancellationTokenSource == nullptr || _cancellationTokenSource->Token()->IsCancellationRequested())
    {
        _cancellationTokenSource = std::make_unique<CancellationTokenSource>();
        _acceptor = std::async(std::launch::async, &Telebot::Accept, this);
    }
}

void Telebot::Telebot::Stop()
{
    if (_cancellationTokenSource != nullptr && !_cancellationTokenSource->Token()->IsCancellationRequested())
    {
        _cancellationTokenSource->Cancel();
        if (_acceptor.valid()) _acceptor.get();
    }
}

void Telebot::Telebot::SetTimeout(std::int32_t timeout)
{
    if (timeout < 0 || timeout > 100) return;
    _timeout = timeout;
}