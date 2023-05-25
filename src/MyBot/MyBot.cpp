#include "MyBot/MyBot.h"

const std::string MyBot::MyBot::FILE_DIRECTORY = "root/files";
const unsigned char MyBot::MyBot::POOL_MAX_SIZE = 3;
const std::string MyBot::MyBot::OPENAI_USER = "TelegramBot";
const unsigned short MyBot::MyBot::REQUESTS_PER_MINUTE_LIMIT = 3;

MyBot::MyBot::MyBot(const std::map<std::string, std::string>& args)
{
    std::vector<std::string> localisationFileNames;

    for (const std::pair<std::string, std::string>& pair : args)
    {
        if (pair.first == "bottoken") _bot = std::make_unique<Telebot::Telebot>(pair.second);
        else if (pair.first == "openaitoken") _openAI = std::make_unique<OpenAI::OpenAI>(pair.second);
        else if (pair.first == "connectionstring") _dbConnection = std::make_unique<DbProvider::DbConnection>(pair.second, POOL_MAX_SIZE);
        else if (pair.first.find("localisation") == 0) localisationFileNames.push_back(pair.second);
    }

    _environment = std::make_shared<Environment>(localisationFileNames);
    _requestsPerLastMinute = 0;

    *_bot->OnCommand("start") += THIS_METHOD_HANDLER(&MyBot::StartCommand)
    *_bot->OnCommand("gpt") += THIS_METHOD_HANDLER(&MyBot::GptSession)
    *_bot->OnCommand("whisper") += THIS_METHOD_HANDLER(&MyBot::WhisperSession)
    *_bot->OnCommand("dalle") += THIS_METHOD_HANDLER(&MyBot::DalleSession)
    *_bot->OnCommand("usage") += THIS_METHOD_HANDLER(&MyBot::GetUsageInfo)
    *_bot->OnCommand("payment") += THIS_METHOD_HANDLER(&MyBot::GetPayment)
    *_bot->OnCommand("help") += THIS_METHOD_HANDLER(&MyBot::GetHelp)
    *_bot->OnCommand("settings") += THIS_METHOD_HANDLER(&MyBot::SetSettings)

    *_bot->OnCallbackQuery("gpt_help_button_clicked") += THIS_METHOD_HANDLER(&MyBot::GetGptHelp)
    *_bot->OnCallbackQuery("whisper_help_button_clicked") += THIS_METHOD_HANDLER(&MyBot::GetWhisperHelp)
    *_bot->OnCallbackQuery("dalle_help_button_clicked") += THIS_METHOD_HANDLER(&MyBot::GetDalleHelp)
    *_bot->OnCallbackQuery("gpt_settings_button_clicked") += THIS_METHOD_HANDLER(&MyBot::SetGptSettings)
    *_bot->OnCallbackQuery("whisper_settings_button_clicked") += THIS_METHOD_HANDLER(&MyBot::SetWhisperSettings)
    *_bot->OnCallbackQuery("dalle_settings_button_clicked") += THIS_METHOD_HANDLER(&MyBot::SetDalleSettings)
    *_bot->OnCallbackQuery("language_settings_button_clicked") += THIS_METHOD_HANDLER(&MyBot::SetLanguage)

    *_bot->OnAnyMessage() += THIS_METHOD_HANDLER(&MyBot::Chat)
    *_bot->OnAnyMessage() += THIS_METHOD_HANDLER(&MyBot::CreateImage)
    *_bot->OnVoice() += THIS_METHOD_HANDLER(&MyBot::Transcript)
}

MyBot::MyBot::~MyBot()
{
    Stop();
}

std::future<bool> MyBot::MyBot::IsUser(std::int64_t userId)
{
    std::function<bool(pqxx::work&, std::int64_t)> transaction =
            [](pqxx::work& work, const std::int64_t& userId)->bool
            {
                std::string query = "SELECT EXISTS(SELECT 1 FROM \"Users\" WHERE userid = " + std::to_string(userId) + ")";
                return work.query_value<bool>(query);
            };

    return _dbConnection->TransactAsync<bool, std::int64_t>(transaction, userId);
}

std::future<bool> MyBot::MyBot::AddUser(std::int64_t userId)
{
    std::function<bool(pqxx::work&, std::int64_t)> transaction =
            [](pqxx::work& work, const std::int64_t& userId)->bool
            {
                std::string query = "INSERT INTO \"Users\" (userid) VALUES (" + std::to_string(userId) + ")";
                work.exec(query);
                return true;
            };

    return _dbConnection->TransactAsync<bool, std::int64_t>(transaction, userId);
}

std::future<unsigned short> MyBot::MyBot::GetRole(std::int64_t userId)
{
    std::function<unsigned short(pqxx::work&, std::int64_t)> transaction =
            [](pqxx::work& work, const std::int64_t& userId)->unsigned short
            {
                std::string query = "SELECT roleid FROM \"Users\" WHERE userid = " + std::to_string(userId);
                return work.query_value<unsigned short>(query);
            };

    return _dbConnection->TransactAsync<unsigned short, std::int64_t>(transaction, userId);
}

std::future<bool> MyBot::MyBot::SetRole(std::int64_t userId, unsigned short roleId)
{
    std::function<bool(pqxx::work&, std::int64_t, unsigned short)> transaction =
            [](pqxx::work& work, const std::int64_t& userId, const unsigned short& roleId)->bool
            {
                std::string query = "UPDATE \"Users\" SET roleid = " + std::to_string(roleId) +
                        " WHERE userid = " + std::to_string(userId);
                work.exec(query);
                return true;
            };

    return _dbConnection->TransactAsync<bool, std::int64_t, unsigned short>(transaction, userId, roleId);
}

std::future<int> MyBot::MyBot::GetUsage(std::int64_t userId)
{
    std::function<int(pqxx::work&, std::int64_t)> transaction =
            [](pqxx::work& work, const std::int64_t& userId)->int
            {
                std::string query = "SELECT totalusage FROM \"Users\" WHERE userid = " + std::to_string(userId);
                return work.query_value<int>(query);
            };

    return _dbConnection->TransactAsync<int, std::int64_t>(transaction, userId);
}

std::future<bool> MyBot::MyBot::AddUsage(std::int64_t userId, int usage)
{
    std::function<bool(pqxx::work&, std::int64_t, int)> transaction =
            [](pqxx::work& work, const std::int64_t& userId, const int& usage)->bool
            {
                std::string query = "UPDATE \"Users\" SET totalusage = totalusage + " + std::to_string(usage) +
                                    " WHERE userid = " + std::to_string(userId);
                work.exec(query);
                return true;
            };

    return _dbConnection->TransactAsync<bool, std::int64_t, int>(transaction, userId, usage);
}

std::future<int> MyBot::MyBot::GetUsageLimit(std::int64_t userId)
{
    std::function<int(pqxx::work&, std::int64_t)> transaction =
            [](pqxx::work& work, const std::int64_t& userId)->int
            {
                std::string query = "SELECT usagelimit FROM \"Users\" WHERE userid = " + std::to_string(userId);
                return work.query_value<int>(query);
            };

    return _dbConnection->TransactAsync<int, std::int64_t>(transaction, userId);
}

std::future<bool> MyBot::MyBot::SetUsageLimit(std::int64_t userId, int usageLimit)
{
    std::function<bool(pqxx::work&, std::int64_t, int)> transaction =
            [](pqxx::work& work, const std::int64_t& userId, const int& usageLimit)->bool
            {
                std::string query = "UPDATE \"Users\" SET usagelimit = " + std::to_string(usageLimit) +
                                    " WHERE userid = " + std::to_string(userId);
                work.exec(query);
                return true;
            };

    return _dbConnection->TransactAsync<bool, std::int64_t, int>(transaction, userId, usageLimit);
}

std::future<MyBot::LanguageCode> MyBot::MyBot::GetLanguageCode(std::int64_t userId)
{
    std::function<LanguageCode(pqxx::work&, std::int64_t)> transaction =
            [](pqxx::work& work, const std::int64_t& userId)->LanguageCode
            {
                std::string query = "SELECT languagecode FROM \"Users\" WHERE userid = " + std::to_string(userId);
                auto result = work.query_value<unsigned short>(query);
                return FromInt(result);
            };

    return _dbConnection->TransactAsync<LanguageCode, std::int64_t>(transaction, userId);
}

std::future<bool> MyBot::MyBot::SetLanguageCode(std::int64_t userId, LanguageCode languageCode)
{
    std::function<bool(pqxx::work&, std::int64_t, LanguageCode)> transaction =
            [](pqxx::work& work, const std::int64_t& userId, const LanguageCode& languageCode)->bool
            {
                std::string query = "UPDATE \"Users\" SET languagecode = " + ToString(languageCode) +
                                    " WHERE userid = " + std::to_string(userId);
                work.exec(query);
                return true;
            };

    return _dbConnection->TransactAsync<bool, std::int64_t, LanguageCode>(transaction, userId, languageCode);
}

std::future<unsigned short> MyBot::MyBot::GetContextLimit(std::int64_t userId)
{
    std::function<unsigned short(pqxx::work&, std::int64_t)> transaction =
            [](pqxx::work& work, const std::int64_t& userId)->unsigned short
            {
                // TODO GetContextLimit
                return 3;
            };

    return _dbConnection->TransactAsync<unsigned short, std::int64_t>(transaction, userId);
}

std::future<bool> MyBot::MyBot::SetContextLimit(std::int64_t userId, unsigned short contextLimit)
{
    std::function<bool(pqxx::work&, std::int64_t, unsigned short)> transaction =
            [](pqxx::work& work, const std::int64_t& userId, const unsigned short& contextLimit)->bool
            {
                // TODO GetContextLimit
                return false;
            };

    return _dbConnection->TransactAsync<bool, std::int64_t, unsigned short>(transaction, userId, contextLimit);
}

MyBot::LanguageCode MyBot::MyBot::GetLanguageCodeCash(std::int64_t userId)
{
    if (_languageCodes.find(userId) != _languageCodes.end()) return _languageCodes.at(userId);
    LanguageCode language = GetLanguageCode(userId).get();
    _languageCodes.insert(std::make_pair(userId, language));
    return language;
}

void MyBot::MyBot::SetLanguageCodeCash(std::int64_t userId, LanguageCode languageCode)
{
    auto set = SetLanguageCode(userId, languageCode);
    DB_TASK(set)

    if (_languageCodes.find(userId) != _languageCodes.end()) _languageCodes.at(userId) = languageCode;
    else _languageCodes.insert(std::make_pair(userId, languageCode));
}

void MyBot::MyBot::Accept()
{
    std::vector<std::pair<std::string, std::string>> commands;
    commands.emplace_back("gpt", _environment->GetLexicalItem(LanguageCode::English, "gpt"));
    commands.emplace_back("whisper", _environment->GetLexicalItem(LanguageCode::English, "whisper"));
    commands.emplace_back("dalle", _environment->GetLexicalItem(LanguageCode::English, "dalle"));
    commands.emplace_back("usage", _environment->GetLexicalItem(LanguageCode::English, "usage"));
    commands.emplace_back("payment", _environment->GetLexicalItem(LanguageCode::English, "payment"));
    commands.emplace_back("help", _environment->GetLexicalItem(LanguageCode::English, "help"));
    commands.emplace_back("settings", _environment->GetLexicalItem(LanguageCode::English, "settings"));
    auto setCommandsResult = _bot->SetCommandsAsync(commands);

    _openAiThreadsChecker = std::async(std::launch::async, [this](){ CheckThreads(_openAiThreads, _openAiThreadsMutex); });
    _telebotThreadsChecker = std::async(std::launch::async, [this](){ CheckThreads(_telebotThreads, _telebotThreadsMutex); });
    _dbThreadsChecker = std::async(std::launch::async, [this](){ CheckThreads(_dbThreads, _dbThreadsMutex); });
    _commonChecker = std::async(std::launch::async, [this](){ CheckThreads(_commonThreads, _commonMutex); });

    if (!setCommandsResult.get()) throw std::runtime_error("set command failed");
}

void MyBot::MyBot::Start()
{
    if (_cancellationTokenSource == nullptr || _cancellationTokenSource->Token()->IsCancellationRequested())
    {
        _cancellationTokenSource = std::make_unique<Common::CancellationTokenSource>();
        Accept();
        _bot->Start();
    }
}

void MyBot::MyBot::StartAsync()
{
    if (_cancellationTokenSource == nullptr || _cancellationTokenSource->Token()->IsCancellationRequested())
    {
        _cancellationTokenSource = std::make_unique<Common::CancellationTokenSource>();
        Accept();
        _bot->StartAsync();
    }
}

void MyBot::MyBot::Stop()
{
    if (_cancellationTokenSource == nullptr || _cancellationTokenSource->Token()->IsCancellationRequested()) return;
    _cancellationTokenSource->Cancel();

    std::unique_lock<std::mutex> queueLock(_openAiThreadsMutex);
    for (auto& task : _openAiThreads) task.get();
    queueLock.unlock();

    std::unique_lock<std::mutex> telebotLock(_telebotThreadsMutex);
    for (auto& task : _telebotThreads) task.get();
    telebotLock.unlock();

    std::unique_lock<std::mutex> dbLock(_dbThreadsMutex);
    for (auto& task : _dbThreads) task.get();
    dbLock.unlock();

    std::unique_lock<std::mutex> commonLock(_commonMutex);
    for (auto& task : _commonThreads) task.get();
    commonLock.unlock();

    _openAiThreadsChecker.wait();
    _telebotThreadsChecker.wait();
    _dbThreadsChecker.wait();
    _commonChecker.wait();
}

void MyBot::MyBot::SetLogger(const std::string& logConfigPath)
{
    _logger = std::make_shared<CInfoLog::Logger>(logConfigPath);
}

void MyBot::MyBot::StartCommand(const Telebot::Message::Ptr& message)
{
    auto start = std::async(std::launch::async, [this, message]()
    {
        std::int64_t id = message->from->id;
        if (!IsUser(id).get()) AddUser(id).get();
        SetLanguageCodeCash(id, LanguageCode::English);
    });

    COMMON_TASK(start)
}

void MyBot::MyBot::GptSession(const Telebot::Message::Ptr& message)
{
    auto session = std::async(std::launch::async, [this, message]()
    {
        std::int64_t id = message->from->id;
        if (!IsUser(id).get()) AddUser(id).get();
        OpenAI::OpenAIModel::Ptr chatGpt = _openAI->GptTurboSession(std::to_string(id), OPENAI_USER, OpenAI::Role::User);

        if (_openAiSessions.find(id) == _openAiSessions.end()) _openAiSessions.insert(std::make_pair(id, chatGpt));
        else _openAiSessions[id] = chatGpt;

        Telebot::InlineKeyboardButton::Ptr helpButton = std::make_shared<Telebot::InlineKeyboardButton>();
        helpButton->text = "help";
        helpButton->callback_data = "gpt_help_button_clicked";

        Telebot::InlineKeyboardButton::Ptr settingButton = std::make_shared<Telebot::InlineKeyboardButton>();
        settingButton->text = "settings";
        settingButton->callback_data = "gpt_settings_button_clicked";

        Telebot::InlineKeyboardMarkup::Ptr keyboard = std::make_shared<Telebot::InlineKeyboardMarkup>();
        keyboard->SetButton(helpButton, 0, 0);
        keyboard->SetButton(settingButton, 0, 1);

        auto send = _bot->SendMessageAsync(id, _environment->GetLexicalItem(GetLanguageCodeCash(id), "gpthellow"), keyboard);
    });

    COMMON_TASK(session)
}

void MyBot::MyBot::WhisperSession(const Telebot::Message::Ptr& message)
{
    auto session = std::async(std::launch::async, [this, message]()
    {
        std::int64_t id = message->from->id;
        if (!IsUser(id).get()) AddUser(id).get();
        OpenAI::OpenAIModel::Ptr whisper = _openAI->WhisperSession();

        if (_openAiSessions.find(id) == _openAiSessions.end()) _openAiSessions.insert(std::make_pair(id, whisper));
        else _openAiSessions[id] = whisper;

        Telebot::InlineKeyboardButton::Ptr helpButton = std::make_shared<Telebot::InlineKeyboardButton>();
        helpButton->text = "help";
        helpButton->callback_data = "whisper_help_button_clicked";

        Telebot::InlineKeyboardButton::Ptr settingButton = std::make_shared<Telebot::InlineKeyboardButton>();
        settingButton->text = "settings";
        settingButton->callback_data = "whisper_settings_button_clicked";

        Telebot::InlineKeyboardMarkup::Ptr keyboard = std::make_shared<Telebot::InlineKeyboardMarkup>();
        keyboard->SetButton(helpButton, 0, 0);
        keyboard->SetButton(settingButton, 0, 1);

        auto send = _bot->SendMessageAsync(id, _environment->GetLexicalItem(GetLanguageCodeCash(id), "whisperhellow"), keyboard);
    });

    COMMON_TASK(session)
}

void MyBot::MyBot::DalleSession(const Telebot::Message::Ptr& message)
{
    auto session = std::async(std::launch::async, [this, message]()
    {
        std::int64_t id = message->from->id;
        if (!IsUser(id).get()) AddUser(id).get();
        OpenAI::OpenAIModel::Ptr dalle = _openAI->DalleSession(std::to_string(id));

        if (_openAiSessions.find(id) == _openAiSessions.end()) _openAiSessions.insert(std::make_pair(id, dalle));
        else _openAiSessions[id] = dalle;

        Telebot::InlineKeyboardButton::Ptr helpButton = std::make_shared<Telebot::InlineKeyboardButton>();
        helpButton->text = "help";
        helpButton->callback_data = "dalle_help_button_clicked";

        Telebot::InlineKeyboardButton::Ptr settingButton = std::make_shared<Telebot::InlineKeyboardButton>();
        settingButton->text = "settings";
        settingButton->callback_data = "dalle_settings_button_clicked";

        Telebot::InlineKeyboardMarkup::Ptr keyboard = std::make_shared<Telebot::InlineKeyboardMarkup>();
        keyboard->SetButton(helpButton, 0, 0);
        keyboard->SetButton(settingButton, 0, 1);

        auto send = _bot->SendMessageAsync(id, _environment->GetLexicalItem(GetLanguageCodeCash(id), "dallehellow"), keyboard);
    });

    COMMON_TASK(session)
}

void MyBot::MyBot::GetUsageInfo(const Telebot::Message::Ptr& message)
{
    auto get = std::async(std::launch::async, [this, message]()
    {
        std::int64_t id = message->from->id;
        if (!IsUser(id).get()) AddUser(id).get();

        std::future<int> totalUsageFuture = GetUsage(id);
        std::future<int> usageLimitFuture = GetUsageLimit(id);

        int totalUsage = totalUsageFuture.get();
        int usageLimit = usageLimitFuture.get();

        auto send = _bot->SendMessageAsync(id, _environment->GetLexicalItem(GetLanguageCodeCash(id), "youhave") +
            std::to_string(usageLimit - totalUsage) +
            _environment->GetLexicalItem(GetLanguageCodeCash(id), "tokens"));
    });

    COMMON_TASK(get)
}

void MyBot::MyBot::GetPayment(const Telebot::Message::Ptr& message)
{
    auto get = std::async(std::launch::async, [this, message]()
    {
        // TODO payment
    });

    COMMON_TASK(get)
}

void MyBot::MyBot::GetHelp(const Telebot::Message::Ptr& message)
{
    auto get = std::async(std::launch::async, [this, message]()
    {
        Telebot::InlineKeyboardButton::Ptr gptHelpButton = std::make_shared<Telebot::InlineKeyboardButton>();
        gptHelpButton->text = "gpt";
        gptHelpButton->callback_data = "gpt_help_button_clicked";

        Telebot::InlineKeyboardButton::Ptr whisperHelpButton = std::make_shared<Telebot::InlineKeyboardButton>();
        whisperHelpButton->text = "whisper";
        whisperHelpButton->callback_data = "whisper_help_button_clicked";

        Telebot::InlineKeyboardButton::Ptr dalleHelpButton = std::make_shared<Telebot::InlineKeyboardButton>();
        dalleHelpButton->text = "dalle";
        dalleHelpButton->callback_data = "dalle_help_button_clicked";

        Telebot::InlineKeyboardMarkup::Ptr keyboard = std::make_shared<Telebot::InlineKeyboardMarkup>();
        keyboard->SetButton(gptHelpButton, 0, 0);
        keyboard->SetButton(whisperHelpButton, 0, 1);
        keyboard->SetButton(dalleHelpButton, 0, 2);

        auto send = _bot->SendMessageAsync(message->from->id,
                                           _environment->GetLexicalItem(GetLanguageCodeCash(message->from->id), "gethelp"),
                                           keyboard);
    });

    COMMON_TASK(get)
}

void MyBot::MyBot::SetSettings(const Telebot::Message::Ptr& message)
{
    auto set = std::async(std::launch::async, [this, message]()
    {
        Telebot::InlineKeyboardButton::Ptr gptSettingButton = std::make_shared<Telebot::InlineKeyboardButton>();
        gptSettingButton->text = "settings";
        gptSettingButton->callback_data = "gpt_settings_button_clicked";

        Telebot::InlineKeyboardButton::Ptr whisperSettingButton = std::make_shared<Telebot::InlineKeyboardButton>();
        whisperSettingButton->text = "settings";
        whisperSettingButton->callback_data = "whisper_settings_button_clicked";

        Telebot::InlineKeyboardButton::Ptr dalleSettingButton = std::make_shared<Telebot::InlineKeyboardButton>();
        dalleSettingButton->text = "settings";
        dalleSettingButton->callback_data = "dalle_settings_button_clicked";

        Telebot::InlineKeyboardButton::Ptr languageSettingButton = std::make_shared<Telebot::InlineKeyboardButton>();
        languageSettingButton->text = "language";
        languageSettingButton->callback_data = "language_settings_button_clicked";

        Telebot::InlineKeyboardMarkup::Ptr keyboard = std::make_shared<Telebot::InlineKeyboardMarkup>();
        keyboard->SetButton(gptSettingButton, 0, 0);
        keyboard->SetButton(whisperSettingButton, 0, 1);
        keyboard->SetButton(dalleSettingButton, 0, 2);
        keyboard->SetButton(languageSettingButton, 0, 3);

        auto send = _bot->SendMessageAsync(message->from->id,
                                           _environment->GetLexicalItem(GetLanguageCodeCash(message->from->id), "setsettings"),
                                           keyboard);
    });

    COMMON_TASK(set)
}

void MyBot::MyBot::GetGptHelp(const Telebot::CallbackQuery::Ptr& callback)
{
    auto asyncCallback = std::async(std::launch::async, [this, callback]()
    {
        auto send = _bot->SendMessageAsync(callback->from->id,
                                           _environment->GetLexicalItem(GetLanguageCodeCash(callback->from->id), "gpthelp"));
        send.get();
        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);
    });

    COMMON_TASK(asyncCallback)
}

void MyBot::MyBot::GetWhisperHelp(const Telebot::CallbackQuery::Ptr& callback)
{
    auto asyncCallback = std::async(std::launch::async, [this, callback]()
    {
        auto send = _bot->SendMessageAsync(callback->from->id,
                                           _environment->GetLexicalItem(GetLanguageCodeCash(callback->from->id), "whisperhelp"));
        send.get();
        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);
    });

    COMMON_TASK(asyncCallback)
}

void MyBot::MyBot::GetDalleHelp(const Telebot::CallbackQuery::Ptr& callback)
{
    auto asyncCallback = std::async(std::launch::async, [this, callback]()
    {
        auto send = _bot->SendMessageAsync(callback->from->id,
                                           _environment->GetLexicalItem(GetLanguageCodeCash(callback->from->id), "dallehelp"));
        send.get();
        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);
    });

    COMMON_TASK(asyncCallback)
}

void MyBot::MyBot::SetGptSettings(const Telebot::CallbackQuery::Ptr& callback)
{
    auto asyncCallback = std::async(std::launch::async, [this, callback]()
    {
        // TODO SetGptSettings
        auto send = _bot->SendMessageAsync(callback->from->id, callback->data);
        send.get();
        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);
    });

    COMMON_TASK(asyncCallback)
}

void MyBot::MyBot::SetWhisperSettings(const Telebot::CallbackQuery::Ptr& callback)
{
    // TODO SetWhisperSettings
    auto asyncCallback = std::async(std::launch::async, [this, callback]()
    {
        auto send = _bot->SendMessageAsync(callback->from->id, callback->data);
        send.get();
        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);
    });

    COMMON_TASK(asyncCallback)
}

void MyBot::MyBot::SetDalleSettings(const Telebot::CallbackQuery::Ptr& callback)
{
    // TODO SetDalleSettings
    auto asyncCallback = std::async(std::launch::async, [this, callback]()
    {
        auto send = _bot->SendMessageAsync(callback->from->id, callback->data);
        send.get();
        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);
    });

    COMMON_TASK(asyncCallback)
}

void MyBot::MyBot::SetLanguage(const Telebot::CallbackQuery::Ptr& callback)
{
    // TODO SetLanguage
    auto asyncCallback = std::async(std::launch::async, [this, callback]()
    {
        auto send = _bot->SendMessageAsync(callback->from->id, callback->data);
        send.get();
        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);
    });

    COMMON_TASK(asyncCallback)
}

void MyBot::MyBot::Chat(const Telebot::Message::Ptr& message)
{
    std::int64_t id = message->from->id;
    if (_openAiSessions.find(id) == _openAiSessions.end() || _openAiSessions[id]->GetModelName() != "gpt-3.5-turbo") return;

    std::future<bool> chat = AddToQueue<bool>([this](const OpenAI::OpenAIModel::Ptr& model,
                                                     const Telebot::Message::Ptr& message)->bool
    {
        std::int64_t id = message->from->id;
        std::shared_ptr<OpenAI::GptTurbo> gptTurbo = std::dynamic_pointer_cast<OpenAI::GptTurbo>(_openAiSessions[id]);
        if (gptTurbo == nullptr || !UserHasTokens(id)) return false;

        std::pair<std::string, int> answer = gptTurbo->Chat(message->text);

        auto send = _bot->SendMessageAsync(id, answer.first);
        TELEBOT_TASK(send)

        auto addUsage = AddUsage(id, answer.second);
        DB_TASK(addUsage)

        return true;
    }, _openAiSessions[id], message);

    OPENAI_TASK(chat)
}

void MyBot::MyBot::Transcript(const Telebot::Message::Ptr& message)
{
    std::int64_t id = message->from->id;
    if (_openAiSessions.find(id) == _openAiSessions.end() || _openAiSessions[id]->GetModelName() != "whisper-1") return;

    std::future<bool> transcript = AddToQueue<bool>([this](const OpenAI::OpenAIModel::Ptr& model,
                                                           const Telebot::Message::Ptr& message)->bool
    {
        std::int64_t id = message->from->id;
        std::string directory = FILE_DIRECTORY + "/" + std::to_string(id) + "/voice";
        boost::filesystem::path path(directory);
        {
            std::unique_lock<std::mutex> lock(_commonMutex);
            if (!boost::filesystem::exists(path))
                boost::filesystem::create_directories(path);
            lock.unlock();
        }

        auto onLoad = _bot->DownloadFileAsync(message->voice->file_id, directory);
        std::string filePath = onLoad.get();
        ConvertAudio(filePath);

        std::shared_ptr<OpenAI::Whisper> whisper = std::dynamic_pointer_cast<OpenAI::Whisper>(_openAiSessions[id]);
        if (whisper == nullptr || !UserHasTokens(id)) return false;

        std::string answer = whisper->Transcript(filePath + ".mp3");

        auto send = _bot->SendMessageAsync(id, answer);
        TELEBOT_TASK(send)

        auto addUsage = AddUsage(id, message->voice->duration * 50);
        DB_TASK(addUsage)

        {
            std::unique_lock<std::mutex> lock(_commonMutex);
            boost::filesystem::path fileOGA(filePath);
            if (boost::filesystem::exists(filePath)) boost::filesystem::remove(fileOGA);
            boost::filesystem::path fileMp3(filePath + ".mp3");
            if (boost::filesystem::exists(filePath + ".mp3")) boost::filesystem::remove(fileMp3);
            lock.unlock();
        }

        return true;
    }, _openAiSessions[id], message);

    OPENAI_TASK(transcript)
}

void MyBot::MyBot::ConvertAudio(const std::string& filePath)
{
    if (boost::filesystem::exists(filePath + ".mp3")) return;
    std::string command = "ffmpeg -i " + filePath + " " + filePath + ".mp3";
    boost::process::child process(command);
    process.wait();
}

void MyBot::MyBot::CreateImage(const Telebot::Message::Ptr& message)
{
    std::int64_t id = message->from->id;
    if (_openAiSessions.find(id) == _openAiSessions.end() || _openAiSessions[id]->GetModelName() != "DALLE") return;

    std::future<bool> create = AddToQueue<bool>([this](const OpenAI::OpenAIModel::Ptr& model,
                                                       const Telebot::Message::Ptr& message)->bool
    {
        std::int64_t id = message->from->id;
        std::shared_ptr<OpenAI::Dalle> dalle = std::dynamic_pointer_cast<OpenAI::Dalle>(_openAiSessions[id]);
        if (dalle == nullptr || !UserHasTokens(id)) return false;

        std::string url = dalle->CreateImage(message->text, OpenAI::Size::Large);

        auto send = _bot->SendPhotoAsync(id, url);
        TELEBOT_TASK(send)

        auto addUsage = AddUsage(id, 10000);
        DB_TASK(addUsage)

        return true;
    }, _openAiSessions[id], message);

    OPENAI_TASK(create)
}

bool MyBot::MyBot::UserHasTokens(std::int64_t userId)
{
    std::future<int> totalUsageFuture = GetUsage(userId);
    std::future<int> usageLimitFuture = GetUsageLimit(userId);

    int totalUsage = totalUsageFuture.get();
    int usageLimit = usageLimitFuture.get();

    if (totalUsage < usageLimit) return true;

    auto send = _bot->SendMessageAsync(userId, _environment->GetLexicalItem(GetLanguageCodeCash(userId), "havenottokens"));
    TELEBOT_TASK(send)

    return false;
}