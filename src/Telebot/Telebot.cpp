#include "Telebot.h"

const std::int32_t Telebot::Telebot::LIMIT = 100;

Telebot::Telebot::Telebot(const std::string &token)
{
    _api = std::make_unique<TelebotApi>(token);
    _timeout = 10;
    _onAnyMessage = std::make_shared<Common::Event<const Message::Ptr&>>();
    _onVoice = std::make_shared<Common::Event<const Message::Ptr&>>();
    _onAnyCallbackQuery = std::make_shared<Common::Event<const CallbackQuery::Ptr&>>();
}

Telebot::Telebot::~Telebot()
{
    Stop();
}

void Telebot::Telebot::Accept()
{
    std::int32_t offset = 0;
    std::vector<std::string> allowedUpdates;
    allowedUpdates.emplace_back("message");
    allowedUpdates.emplace_back("callback_query");

    while (!_acceptorTokenSource->Token()->IsCancellationRequested())
    {
        std::vector<Update::Ptr> updates = _api->GetUpdates(offset, LIMIT, _timeout, allowedUpdates);
        if (updates.empty()) continue;

        for (const Update::Ptr& update : updates)
        {
            if (update->message.get() != nullptr)
            {
                if (!update->message->text.empty())
                {
                    if (update->message->text[0] == '/')
                    {
                        if (_onCommand.find(update->message->text.substr(1)) != _onCommand.end())
                            (*_onCommand[update->message->text.substr(1)])(update->message);
                    }
                    else
                    {
                        if (_onMessage.find(update->message->text) != _onMessage.end())
                            (*_onMessage[update->message->text])(update->message);

                        (*_onAnyMessage)(update->message);
                    }
                }

                if (update->message->voice.get() != nullptr)
                {
                    (*_onVoice)(update->message);
                }
            }

            if (update->callback_query.get() != nullptr)
            {
                if (_onCallbackQuery.find(update->callback_query->data) != _onCallbackQuery.end())
                    (*_onCallbackQuery[update->callback_query->data])(update->callback_query);

                (*_onAnyCallbackQuery)(update->callback_query);
            }
        }

        offset = updates[updates.size() - 1]->update_id + 1;
    }
}

void Telebot::Telebot::Start()
{
    if (_acceptorTokenSource == nullptr || _acceptorTokenSource->Token()->IsCancellationRequested())
    {
        _acceptorTokenSource = std::make_unique<Common::CancellationTokenSource>();
        User::Ptr user = _api->GetMe();
        if (!user->is_bot) throw std::runtime_error("user is not bot");
        Accept();
    }
}

void Telebot::Telebot::StartAsync()
{
    if (_acceptorTokenSource == nullptr || _acceptorTokenSource->Token()->IsCancellationRequested())
    {
        _acceptorTokenSource = std::make_unique<Common::CancellationTokenSource>();
        User::Ptr user = _api->GetMe();
        if (!user->is_bot) throw std::runtime_error("user is not bot");
        _acceptor = std::async(std::launch::async, [this](){ Accept(); });
    }
}

void Telebot::Telebot::Stop()
{
    if (_acceptorTokenSource == nullptr || _acceptorTokenSource->Token()->IsCancellationRequested()) return;
    _acceptorTokenSource->Cancel();
    _acceptor.wait();
}

void Telebot::Telebot::SetTimeout(std::int32_t timeout)
{
    if (timeout < 0 || timeout > 100) return;
    _timeout = timeout;
}

std::future<Telebot::Message::Ptr> Telebot::Telebot::SendMessageAsync(const std::int64_t& chatId, const std::string& text,
                                                                      const GenericReply::Ptr& genericReply)
{
    return std::async(std::launch::async, [this, chatId, text, genericReply]()
        { return _api->SendMessage(chatId, text, false, 0, genericReply); });
}

std::future<bool> Telebot::Telebot::SetCommandAsync(const std::string& command, const std::string& description)
{
    BotCommand::Ptr commandPtr = std::make_shared<BotCommand>(command, description);
    std::shared_ptr<std::vector<BotCommand::Ptr>> commands = std::make_shared<std::vector<BotCommand::Ptr>>();
    commands->push_back(commandPtr);
    return std::async(std::launch::async, [this, commands](){ return _api->SetMyCommands(*commands); });
}

std::future<bool> Telebot::Telebot::SetCommandAsync(const BotCommand::Ptr& command)
{
    std::shared_ptr<std::vector<BotCommand::Ptr>> commands = std::make_shared<std::vector<BotCommand::Ptr>>();
    commands->push_back(command);
    return std::async(std::launch::async, [this, commands](){ return _api->SetMyCommands(*commands); });
}

std::future<bool> Telebot::Telebot::SetCommandsAsync(const std::vector<std::pair<std::string, std::string>>& commands)
{
    std::shared_ptr<std::vector<BotCommand::Ptr>> commandsPtr = std::make_shared<std::vector<BotCommand::Ptr>>();
    for (const auto& command : commands)
    {
        BotCommand::Ptr commandPtr = std::make_shared<BotCommand>(command.first, command.second);
        commandsPtr->push_back(commandPtr);
    }
    return std::async(std::launch::async, [this, commandsPtr](){ return _api->SetMyCommands(*commandsPtr); });
}

std::future<bool> Telebot::Telebot::SetCommandsAsync(const std::vector<BotCommand::Ptr>& commands)
{
    return std::async(std::launch::async, [this, commands](){ return _api->SetMyCommands(commands); });
}

std::future<std::string> Telebot::Telebot::DownloadFileAsync(const std::string& fileId, const std::string& toDirectory)
{
    return std::async(std::launch::async, [this, fileId, toDirectory]()
    {
        File::Ptr file = _api->GetFile(fileId);
        return _api->DownloadFile(file, toDirectory);
    });
}

std::future<Telebot::Message::Ptr> Telebot::Telebot::SendPhotoAsync(const std::int64_t& chatId,
                                                                    const boost::variant<std::string, InputFile::Ptr>& photo)
{
    return std::async(std::launch::async, [this, chatId, photo](){ return _api->SendPhoto(chatId, photo); });
}

std::future<bool> Telebot::Telebot::AnswerCallbackQueryAsync(const std::string& callbackQueryId, const std::string& text,
                                                             const bool& showAlert)
{
    return std::async(std::launch::async, [this, callbackQueryId, text, showAlert]()
        { return _api->AnswerCallbackQuery(callbackQueryId, text, showAlert); });
}

MessageEvent Telebot::Telebot::OnAnyMessage()
{
    return _onAnyMessage;
}

MessageEvent Telebot::Telebot::OnMessage(const std::string& message)
{
    if (_onMessage.find(message) == _onMessage.end())
        _onMessage.insert(std::make_pair(message, std::make_shared<Common::Event<const Message::Ptr&>>()));
    return _onMessage[message];
}

MessageEvent Telebot::Telebot::OnCommand(const std::string& command)
{
    if (_onCommand.find(command) == _onCommand.end())
        _onCommand.insert(std::make_pair(command, std::make_shared<Common::Event<const Message::Ptr&>>()));
    return _onCommand[command];
}

MessageEvent Telebot::Telebot::OnVoice()
{
    return _onVoice;
}

CallbackQueryEvent Telebot::Telebot::OnAnyCallbackQuery()
{
    return _onAnyCallbackQuery;
}

CallbackQueryEvent Telebot::Telebot::OnCallbackQuery(const std::string& callback_data)
{
    if (_onCallbackQuery.find(callback_data) == _onCallbackQuery.end())
        _onCallbackQuery.insert(std::make_pair(callback_data, std::make_shared<Common::Event<const CallbackQuery::Ptr&>>()));
    return _onCallbackQuery[callback_data];
}