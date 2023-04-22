#include "Bot.h"

const std::int32_t Telebot::Bot::LIMIT = 100;

Telebot::Bot::Bot(const std::string &token)
{
    _api = std::make_unique<BotApi>(token);
    _timeout = 10;
    _onAnyMessage = std::make_shared<Common::Event<const Message::Ptr&>>();

    User::Ptr user = _api->GetMe();
    if (!user->is_bot) throw std::runtime_error("user is not bot");
}

Telebot::Bot::~Bot()
{
    Stop();
}

void Telebot::Bot::Accept()
{
    std::int32_t offset = 0;
    std::vector<std::string> allowedUpdates;
    allowedUpdates.emplace_back("message");

    while (!_cancellationTokenSource->Token()->IsCancellationRequested())
    {
        std::vector<Update::Ptr> updates = _api->GetUpdates(offset, LIMIT, _timeout, allowedUpdates);
        if (updates.empty()) continue;

        for (const Update::Ptr& update : updates)
        {
            if (update->message.get() != nullptr)
            {
                if (update->message->text[0] == '/')
                {
                    if (_onCommand.find(update->message->text.substr(1)) != _onCommand.end())
                        (*_onCommand[update->message->text.substr(1)])(update->message);
                }
                else
                {
                    (*_onAnyMessage)(update->message);

                    if (_onMessage.find(update->message->text) != _onMessage.end())
                        (*_onMessage[update->message->text])(update->message);
                }

            }
        }

        offset = updates[updates.size() - 1]->update_id + 1;
    }
}

void Telebot::Bot::Start()
{
    if (_cancellationTokenSource == nullptr || _cancellationTokenSource->Token()->IsCancellationRequested())
    {
        _cancellationTokenSource = std::make_unique<Common::CancellationTokenSource>();
        Accept();
    }
}

void Telebot::Bot::StartAsync()
{
    if (_cancellationTokenSource == nullptr || _cancellationTokenSource->Token()->IsCancellationRequested())
    {
        _cancellationTokenSource = std::make_unique<Common::CancellationTokenSource>();
        _acceptor = std::async(std::launch::async, &Bot::Accept, this);
    }
}

void Telebot::Bot::Stop()
{
    if (_cancellationTokenSource != nullptr && !_cancellationTokenSource->Token()->IsCancellationRequested())
    {
        _cancellationTokenSource->Cancel();
        if (_acceptor.valid()) _acceptor.get();
    }
}

void Telebot::Bot::SetTimeout(std::int32_t timeout)
{
    if (timeout < 0 || timeout > 100) return;
    _timeout = timeout;
}

std::future<Telebot::Message::Ptr> Telebot::Bot::SendMessageAsync(std::int64_t chatId, const std::string& text)
{
    return std::async(std::launch::async, [this, &chatId, text](){ return _api->SendMessage(chatId, text); });
}

std::future<bool> Telebot::Bot::SetCommandAsync(const std::string& command, const std::string& description)
{
    BotCommand::Ptr commandPtr = std::make_shared<BotCommand>(command, description);
    std::shared_ptr<std::vector<BotCommand::Ptr>> commands = std::make_shared<std::vector<BotCommand::Ptr>>();
    commands->push_back(commandPtr);
    return std::async(std::launch::async, [this, commands](){ return _api->SetMyCommands(*commands); });
}

std::future<bool> Telebot::Bot::SetCommandAsync(const BotCommand::Ptr& command)
{
    std::shared_ptr<std::vector<BotCommand::Ptr>> commands = std::make_shared<std::vector<BotCommand::Ptr>>();
    commands->push_back(command);
    return std::async(std::launch::async, [this, commands](){ return _api->SetMyCommands(*commands); });
}

std::future<bool> Telebot::Bot::SetCommandsAsync(const std::vector<BotCommand::Ptr>& commands)
{
    return std::async(std::launch::async, [this, commands](){ return _api->SetMyCommands(commands); });
}

MessageEvent Telebot::Bot::OnAnyMessage()
{
    return _onAnyMessage;
}

MessageEvent Telebot::Bot::OnMessage(const std::string& message)
{
    if (_onMessage.find(message) == _onMessage.end())
        _onMessage.insert(std::make_pair(message, std::make_shared<Common::Event<const Message::Ptr&>>()));
    return _onMessage[message];
}

MessageEvent Telebot::Bot::OnCommand(const std::string& command)
{
    if (_onCommand.find(command) == _onCommand.end())
        _onCommand.insert(std::make_pair(command, std::make_shared<Common::Event<const Message::Ptr&>>()));
    return _onCommand[command];
}