#include "MyBot/MyBot.h"

const std::string MyBot::MyBot::FILE_DIRECTORY = "root/files";
const std::string MyBot::MyBot::OPENAI_USER = "TelegramBot";
const unsigned short MyBot::MyBot::REQUESTS_PER_MINUTE_LIMIT = 3;

MyBot::MyBot::MyBot(const std::map<std::string, std::string>& args)
{
    std::vector<std::string> localisationFileNames;

    for (const auto& pair : args)
    {
        if (pair.first == "bottoken") _bot = std::make_unique<Telebot::Telebot>(pair.second);
        else if (pair.first == "openaitoken") _openAI = std::make_unique<OpenAI::OpenAI>(pair.second);
        else if (pair.first == "connectionstring") _dbRequest = std::make_shared<DbRequest>(pair.second);
        else if (pair.first.find("localisation") == 0) localisationFileNames.push_back(pair.second);
    }

    _dbCash = std::make_unique<DbCash>(_dbRequest);
    _environment = std::make_shared<Environment>(localisationFileNames);
    _requestsPerLastMinute = 0;

    *_bot->OnCommand("start") += THIS_METHOD_HANDLER(&MyBot::StartCommand);
    *_bot->OnCommand("gpt") += THIS_METHOD_HANDLER(&MyBot::GptSession);
    *_bot->OnCommand("whisper") += THIS_METHOD_HANDLER(&MyBot::WhisperSession);
    *_bot->OnCommand("dalle") += THIS_METHOD_HANDLER(&MyBot::DalleSession);
    *_bot->OnCommand("usage") += THIS_METHOD_HANDLER(&MyBot::GetUsageInfo);
    *_bot->OnCommand("payment") += THIS_METHOD_HANDLER(&MyBot::GetPayment);
    *_bot->OnCommand("help") += THIS_METHOD_HANDLER(&MyBot::GetHelp);
    *_bot->OnCommand("settings") += THIS_METHOD_HANDLER(&MyBot::SetSettings);

    *_bot->OnCallbackQuery("gpt_help_button_clicked") += THIS_METHOD_HANDLER(&MyBot::GetGptHelp);
    *_bot->OnCallbackQuery("whisper_help_button_clicked") += THIS_METHOD_HANDLER(&MyBot::GetWhisperHelp);
    *_bot->OnCallbackQuery("dalle_help_button_clicked") += THIS_METHOD_HANDLER(&MyBot::GetDalleHelp);
    *_bot->OnCallbackQuery("gpt_settings_button_clicked") += THIS_METHOD_HANDLER(&MyBot::SetGptSettings);
    *_bot->OnCallbackQuery("whisper_settings_button_clicked") += THIS_METHOD_HANDLER(&MyBot::SetWhisperSettings);
    *_bot->OnCallbackQuery("dalle_settings_button_clicked") += THIS_METHOD_HANDLER(&MyBot::SetDalleSettings);
    *_bot->OnCallbackQuery("language_settings_button_clicked") += THIS_METHOD_HANDLER(&MyBot::SetLanguage);

    *_bot->OnCallbackQuery("gpt_settings_back_button_clicked") += THIS_METHOD_HANDLER(&MyBot::BackGptSettings);
    *_bot->OnCallbackQuery("gpt_context_size_button_clicked") += THIS_METHOD_HANDLER(&MyBot::SetContextSize);
    *_bot->OnCallbackQuery("gpt_temperature_button_clicked") += THIS_METHOD_HANDLER(&MyBot::SetGptTemperature);
    *_bot->OnCallbackQuery("gpt_allow_voice_button_clicked") += THIS_METHOD_HANDLER(&MyBot::SetGptAllowVoice);

    *_bot->OnCallbackQuery("whisper_settings_back_button_clicked") += THIS_METHOD_HANDLER(&MyBot::BackWhisperSettings);
    *_bot->OnCallbackQuery("whisper_temperature_button_clicked") += THIS_METHOD_HANDLER(&MyBot::SetWhisperTemperature);

    *_bot->OnCallbackQuery("dalle_settings_back_button_clicked") += THIS_METHOD_HANDLER(&MyBot::BackDalleSettings);
    *_bot->OnCallbackQuery("dalle_context_size_button_clicked") += THIS_METHOD_HANDLER(&MyBot::SetDalleSize);
    *_bot->OnCallbackQuery("dalle_allow_voice_button_clicked") += THIS_METHOD_HANDLER(&MyBot::SetDalleAllowVoice);

    *_bot->OnCallbackQuery("language_back_button_clicked") += THIS_METHOD_HANDLER(&MyBot::BackLanguageSettings);
    *_bot->OnCallbackQuery("english_button_clicked") += THIS_METHOD_HANDLER(&MyBot::SetEnglish);
    *_bot->OnCallbackQuery("russian_button_clicked") += THIS_METHOD_HANDLER(&MyBot::SetRussian);

    *_bot->OnAnyMessage() += THIS_METHOD_HANDLER(&MyBot::Chat);
    *_bot->OnAnyMessage() += THIS_METHOD_HANDLER(&MyBot::CreateImage);
    *_bot->OnVoice() += THIS_METHOD_HANDLER(&MyBot::Transcript);
}

MyBot::MyBot::~MyBot()
{
    Stop();
}

void MyBot::MyBot::Accept()
{
    std::vector<std::pair<std::string, std::string>> commands;
    commands.emplace_back("gpt", _environment->GetLexicalItem(Language::English, "gpt"));
    commands.emplace_back("whisper", _environment->GetLexicalItem(Language::English, "whisper"));
    commands.emplace_back("dalle", _environment->GetLexicalItem(Language::English, "dalle"));
    commands.emplace_back("usage", _environment->GetLexicalItem(Language::English, "usage"));
    commands.emplace_back("payment", _environment->GetLexicalItem(Language::English, "payment"));
    commands.emplace_back("help", _environment->GetLexicalItem(Language::English, "help"));
    commands.emplace_back("settings", _environment->GetLexicalItem(Language::English, "settings"));
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
        if (!_dbRequest->IsUser(id).get()) _dbRequest->AddUser(id).get();
        _dbCash->SetLanguageCash(id, Language::English);
    });

    COMMON_TASK(start);
}

void MyBot::MyBot::GptSession(const Telebot::Message::Ptr& message)
{
    auto session = std::async(std::launch::async, [this, message]()
    {
        std::int64_t id = message->from->id;
        if (!_dbRequest->IsUser(id).get()) _dbRequest->AddUser(id).get();
        OpenAI::OpenAIModel::Ptr chatGpt = _openAI->GptTurboSession(std::to_string(id), OPENAI_USER);

        if (_openAiSessions.find(id) == _openAiSessions.end()) _openAiSessions.insert(std::make_pair(id, chatGpt));
        else _openAiSessions[id] = chatGpt;

        InlineButton helpButton = INLINE_BUTTON(LEXICAL_ITEM("helpinline"), "gpt_help_button_clicked");
        InlineButton settingButton = INLINE_BUTTON(LEXICAL_ITEM("settingsinline"), "gpt_settings_button_clicked");

        Telebot::InlineKeyboardMarkup::Ptr keyboard = std::make_shared<Telebot::InlineKeyboardMarkup>();
        keyboard->SetButton(helpButton, 0, 0);
        keyboard->SetButton(settingButton, 0, 1);

        auto send = _bot->SendMessageAsync(id, LEXICAL_ITEM("gpthellow"), keyboard);
    });

    COMMON_TASK(session);
}

void MyBot::MyBot::WhisperSession(const Telebot::Message::Ptr& message)
{
    auto session = std::async(std::launch::async, [this, message]()
    {
        std::int64_t id = message->from->id;
        if (!_dbRequest->IsUser(id).get()) _dbRequest->AddUser(id).get();
        OpenAI::OpenAIModel::Ptr whisper = _openAI->WhisperSession();

        if (_openAiSessions.find(id) == _openAiSessions.end()) _openAiSessions.insert(std::make_pair(id, whisper));
        else _openAiSessions[id] = whisper;

        InlineButton helpButton = INLINE_BUTTON(LEXICAL_ITEM("helpinline"), "whisper_help_button_clicked");
        InlineButton settingButton = INLINE_BUTTON(LEXICAL_ITEM("settingsinline"), "whisper_settings_button_clicked");

        Telebot::InlineKeyboardMarkup::Ptr keyboard = std::make_shared<Telebot::InlineKeyboardMarkup>();
        keyboard->SetButton(helpButton, 0, 0);
        keyboard->SetButton(settingButton, 0, 1);

        auto send = _bot->SendMessageAsync(id, LEXICAL_ITEM("whisperhellow"), keyboard);
    });

    COMMON_TASK(session);
}

void MyBot::MyBot::DalleSession(const Telebot::Message::Ptr& message)
{
    auto session = std::async(std::launch::async, [this, message]()
    {
        std::int64_t id = message->from->id;
        if (!_dbRequest->IsUser(id).get()) _dbRequest->AddUser(id).get();
        OpenAI::OpenAIModel::Ptr dalle = _openAI->DalleSession(std::to_string(id));

        if (_openAiSessions.find(id) == _openAiSessions.end()) _openAiSessions.insert(std::make_pair(id, dalle));
        else _openAiSessions[id] = dalle;

        InlineButton helpButton = INLINE_BUTTON(LEXICAL_ITEM("helpinline"), "dalle_help_button_clicked");
        InlineButton settingButton = INLINE_BUTTON(LEXICAL_ITEM("settingsinline"), "dalle_settings_button_clicked");

        Telebot::InlineKeyboardMarkup::Ptr keyboard = std::make_shared<Telebot::InlineKeyboardMarkup>();
        keyboard->SetButton(helpButton, 0, 0);
        keyboard->SetButton(settingButton, 0, 1);

        auto send = _bot->SendMessageAsync(id, LEXICAL_ITEM("dallehellow"), keyboard);
    });

    COMMON_TASK(session);
}

void MyBot::MyBot::GetUsageInfo(const Telebot::Message::Ptr& message)
{
    auto get = std::async(std::launch::async, [this, message]()
    {
        std::int64_t id = message->from->id;
        if (!_dbRequest->IsUser(id).get()) _dbRequest->AddUser(id).get();

        User::Ptr user = _dbCash->GetUserCash(id);
        int totalUsage = user->totalusage;
        int usageLimit = user->usagelimit;

        auto send = _bot->SendMessageAsync(id, _environment->GetLexicalItem(user->language, "youhave") +
                                               std::to_string(usageLimit - totalUsage) +
                                               _environment->GetLexicalItem(user->language, "tokens"));
    });

    COMMON_TASK(get);
}

void MyBot::MyBot::GetPayment(const Telebot::Message::Ptr& message)
{
    auto get = std::async(std::launch::async, [this, message]()
    {
        // TODO payment
    });

    COMMON_TASK(get);
}

void MyBot::MyBot::GetHelp(const Telebot::Message::Ptr& message)
{
    auto get = std::async(std::launch::async, [this, message]()
    {
        std::int64_t id = message->from->id;

        InlineButton gptHelpButton = INLINE_BUTTON("gpt", "gpt_help_button_clicked");
        InlineButton whisperHelpButton = INLINE_BUTTON("whisper", "whisper_help_button_clicked");
        InlineButton dalleHelpButton = INLINE_BUTTON("dalle", "dalle_help_button_clicked");

        Telebot::InlineKeyboardMarkup::Ptr keyboard = std::make_shared<Telebot::InlineKeyboardMarkup>();
        keyboard->SetButton(gptHelpButton, 0, 0);
        keyboard->SetButton(whisperHelpButton, 0, 1);
        keyboard->SetButton(dalleHelpButton, 0, 2);

        auto send = _bot->SendMessageAsync(id, LEXICAL_ITEM("gethelp"), keyboard);
    });

    COMMON_TASK(get);
}

void MyBot::MyBot::SetSettings(const Telebot::Message::Ptr& message)
{
    auto set = std::async(std::launch::async, [this, message]()
    {
        std::int64_t id = message->from->id;

        InlineButton gptSettingButton = INLINE_BUTTON("gpt", "gpt_settings_button_clicked");
        InlineButton whisperSettingButton = INLINE_BUTTON("whisper", "whisper_settings_button_clicked");
        InlineButton dalleSettingButton = INLINE_BUTTON("dalle", "dalle_settings_button_clicked");
        InlineButton languageSettingButton = INLINE_BUTTON(LEXICAL_ITEM("languageinline"), "language_settings_button_clicked");

        Telebot::InlineKeyboardMarkup::Ptr keyboard = std::make_shared<Telebot::InlineKeyboardMarkup>();
        keyboard->SetButton(gptSettingButton, 0, 0);
        keyboard->SetButton(whisperSettingButton, 0, 1);
        keyboard->SetButton(dalleSettingButton, 1, 0);
        keyboard->SetButton(languageSettingButton, 1, 1);

        auto send = _bot->SendMessageAsync(id, LEXICAL_ITEM("setsettings"), keyboard);
    });

    COMMON_TASK(set);
}

void MyBot::MyBot::GetGptHelp(const Telebot::CallbackQuery::Ptr& callback)
{
    auto asyncCallback = std::async(std::launch::async, [this, callback]()
    {
        std::int64_t id = callback->from->id;

        auto send = _bot->SendMessageAsync(id, LEXICAL_ITEM("gpthelp"));
        TELEBOT_TASK(send);

        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);
    });

    COMMON_TASK(asyncCallback);
}

void MyBot::MyBot::GetWhisperHelp(const Telebot::CallbackQuery::Ptr& callback)
{
    auto asyncCallback = std::async(std::launch::async, [this, callback]()
    {
        std::int64_t id = callback->from->id;

        auto send = _bot->SendMessageAsync(id, LEXICAL_ITEM("whisperhelp"));
        TELEBOT_TASK(send);

        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);
    });

    COMMON_TASK(asyncCallback);
}

void MyBot::MyBot::GetDalleHelp(const Telebot::CallbackQuery::Ptr& callback)
{
    auto asyncCallback = std::async(std::launch::async, [this, callback]()
    {
        std::int64_t id = callback->from->id;

        auto send = _bot->SendMessageAsync(id, LEXICAL_ITEM("dallehelp"));
        TELEBOT_TASK(send);

        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);
    });

    COMMON_TASK(asyncCallback);
}

void MyBot::MyBot::SetGptSettings(const Telebot::CallbackQuery::Ptr& callback)
{
    auto asyncCallback = std::async(std::launch::async, [this, callback]()
    {
        std::int64_t id = callback->from->id;

        InlineButton backButton = INLINE_BUTTON("<<", "gpt_settings_back_button_clicked");
        InlineButton contextSizeButton = INLINE_BUTTON(LEXICAL_ITEM("contextsizeinline"), "gpt_context_size_button_clicked");
        InlineButton temperatureButton = INLINE_BUTTON(LEXICAL_ITEM("temperatureinline"), "gpt_temperature_button_clicked");
        InlineButton allowVoiceButton = INLINE_BUTTON(LEXICAL_ITEM("allowvoiceinline"), "gpt_allow_voice_button_clicked");

        Telebot::InlineKeyboardMarkup::Ptr keyboard = std::make_shared<Telebot::InlineKeyboardMarkup>();
        keyboard->SetButton(backButton, 0, 0);
        keyboard->SetButton(contextSizeButton, 0, 1);
        keyboard->SetButton(temperatureButton, 1, 0);
        keyboard->SetButton(allowVoiceButton, 1, 1);

        auto send = _bot->EditMessageTextAsync(id, callback->message->message_id, LEXICAL_ITEM("gptsettings"), keyboard);
        TELEBOT_TASK(send);

        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);
    });

    COMMON_TASK(asyncCallback);
}

void MyBot::MyBot::SetWhisperSettings(const Telebot::CallbackQuery::Ptr& callback)
{
    auto asyncCallback = std::async(std::launch::async, [this, callback]()
    {
        std::int64_t id = callback->from->id;

        InlineButton backButton = INLINE_BUTTON("<<", "whisper_settings_back_button_clicked");
        InlineButton temperatureButton = INLINE_BUTTON(LEXICAL_ITEM("temperatureinline"), "whisper_temperature_button_clicked");

        Telebot::InlineKeyboardMarkup::Ptr keyboard = std::make_shared<Telebot::InlineKeyboardMarkup>();
        keyboard->SetButton(backButton, 0, 0);
        keyboard->SetButton(temperatureButton, 0, 1);

        auto send = _bot->EditMessageTextAsync(id, callback->message->message_id, LEXICAL_ITEM("whispersettings"), keyboard);
        TELEBOT_TASK(send);

        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);
    });

    COMMON_TASK(asyncCallback);
}

void MyBot::MyBot::SetDalleSettings(const Telebot::CallbackQuery::Ptr& callback)
{
    auto asyncCallback = std::async(std::launch::async, [this, callback]()
    {
        std::int64_t id = callback->from->id;

        InlineButton backButton = INLINE_BUTTON("<<", "dalle_settings_back_button_clicked");
        InlineButton sizeButton = INLINE_BUTTON(LEXICAL_ITEM("sizeinline"), "dalle_size_button_clicked");
        InlineButton allowVoiceButton = INLINE_BUTTON(LEXICAL_ITEM("allowvoiceinline"), "dalle_allow_voice_button_clicked");

        Telebot::InlineKeyboardMarkup::Ptr keyboard = std::make_shared<Telebot::InlineKeyboardMarkup>();
        keyboard->SetButton(backButton, 0, 0);
        keyboard->SetButton(sizeButton, 0, 1);
        keyboard->SetButton(allowVoiceButton, 0, 2);

        auto send = _bot->EditMessageTextAsync(id, callback->message->message_id, LEXICAL_ITEM("dallesettings"), keyboard);
        TELEBOT_TASK(send);

        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);
    });

    COMMON_TASK(asyncCallback);
}

void MyBot::MyBot::SetLanguage(const Telebot::CallbackQuery::Ptr& callback)
{
    auto asyncCallback = std::async(std::launch::async, [this, callback]()
    {
        std::int64_t id = callback->from->id;

        InlineButton backButton = INLINE_BUTTON("<<", "language_back_button_clicked");
        InlineButton englishButton = INLINE_BUTTON("English", "english_button_clicked");
        InlineButton russianButton = INLINE_BUTTON("Русский", "russian_button_clicked");

        Telebot::InlineKeyboardMarkup::Ptr keyboard = std::make_shared<Telebot::InlineKeyboardMarkup>();
        keyboard->SetButton(backButton, 0, 0);
        keyboard->SetButton(englishButton, 0, 1);
        keyboard->SetButton(russianButton, 0, 2);

        auto send = _bot->EditMessageTextAsync(id, callback->message->message_id, LEXICAL_ITEM("choicelanguage"), keyboard);
        TELEBOT_TASK(send);

        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);
    });

    COMMON_TASK(asyncCallback);
}

void MyBot::MyBot::BackGptSettings(const Telebot::CallbackQuery::Ptr& callback)
{
    // TODO BackGptSettings
}

void MyBot::MyBot::SetContextSize(const Telebot::CallbackQuery::Ptr& callback)
{
    // TODO SetContextSize
}

void MyBot::MyBot::SetGptTemperature(const Telebot::CallbackQuery::Ptr& callback)
{
    // TODO SetGptTemperature
}

void MyBot::MyBot::SetGptAllowVoice(const Telebot::CallbackQuery::Ptr& callback)
{
    // TODO SetGptAllowVoice
}

void MyBot::MyBot::BackWhisperSettings(const Telebot::CallbackQuery::Ptr& callback)
{
    // TODO BackWhisperSettings
}

void MyBot::MyBot::SetWhisperTemperature(const Telebot::CallbackQuery::Ptr& callback)
{
    // TODO SetWhisperTemperature
}

void MyBot::MyBot::BackDalleSettings(const Telebot::CallbackQuery::Ptr& callback)
{
    // TODO BackDalleSettings
}

void MyBot::MyBot::SetDalleSize(const Telebot::CallbackQuery::Ptr& callback)
{
    // TODO SetDalleSize
}

void MyBot::MyBot::SetDalleAllowVoice(const Telebot::CallbackQuery::Ptr& callback)
{
    // TODO SetDalleAllowVoice
}

void MyBot::MyBot::BackLanguageSettings(const Telebot::CallbackQuery::Ptr& callback)
{
    auto back = std::async(std::launch::async, [this, callback]()
    {
        std::int64_t id = callback->from->id;

        InlineButton gptSettingButton = INLINE_BUTTON("gpt", "gpt_settings_button_clicked");
        InlineButton whisperSettingButton = INLINE_BUTTON("whisper", "whisper_settings_button_clicked");
        InlineButton dalleSettingButton = INLINE_BUTTON("dalle", "dalle_settings_button_clicked");
        InlineButton languageSettingButton = INLINE_BUTTON(LEXICAL_ITEM("languageinline"), "language_settings_button_clicked");

        Telebot::InlineKeyboardMarkup::Ptr keyboard = std::make_shared<Telebot::InlineKeyboardMarkup>();
        keyboard->SetButton(gptSettingButton, 0, 0);
        keyboard->SetButton(whisperSettingButton, 0, 1);
        keyboard->SetButton(dalleSettingButton, 1, 0);
        keyboard->SetButton(languageSettingButton, 1, 1);

        auto send = _bot->EditMessageTextAsync(id, callback->message->message_id, LEXICAL_ITEM("setsettings"), keyboard);
        TELEBOT_TASK(send);

        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);
    });

    COMMON_TASK(back);
}

void MyBot::MyBot::SetEnglish(const Telebot::CallbackQuery::Ptr& callback)
{
    auto set = std::async(std::launch::async, [this, callback]()
    {
        std::int64_t id = callback->from->id;

        auto updateDb = _dbCash->SetLanguageCash(id, Language::English);
        DB_TASK(updateDb);

        auto send = _bot->SendMessageAsync(id, LEXICAL_ITEM("setenglishcompleted"));
        TELEBOT_TASK(send);

        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);
    });

    COMMON_TASK(set);
}

void MyBot::MyBot::SetRussian(const Telebot::CallbackQuery::Ptr& callback)
{
    auto set = std::async(std::launch::async, [this, callback]()
    {
        std::int64_t id = callback->from->id;

        auto updateDb = _dbCash->SetLanguageCash(id, Language::Russian);
        DB_TASK(updateDb);

        auto send = _bot->SendMessageAsync(id, LEXICAL_ITEM("setrussiancompleted"));
        TELEBOT_TASK(send);

        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);
    });

    COMMON_TASK(set);
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
        TELEBOT_TASK(send);

        auto addUsage = _dbCash->AddTotalUsageCash(id, answer.second);
        DB_TASK(addUsage);

        return true;
    }, _openAiSessions[id], message);

    OPENAI_TASK(chat);
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
        TELEBOT_TASK(send);

        auto addUsage = _dbCash->AddTotalUsageCash(id, message->voice->duration * 50);
        DB_TASK(addUsage);

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

    OPENAI_TASK(transcript);
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

        std::string url = dalle->CreateImage(message->text);

        auto send = _bot->SendPhotoAsync(id, url);
        TELEBOT_TASK(send);

        auto addUsage = _dbCash->AddTotalUsageCash(id, 10000);
        DB_TASK(addUsage);

        return true;
    }, _openAiSessions[id], message);

    OPENAI_TASK(create);
}

bool MyBot::MyBot::UserHasTokens(std::int64_t userId)
{
    User::Ptr user = _dbCash->GetUserCash(userId);

    if (user->totalusage < user->usagelimit) return true;

    auto send = _bot->SendMessageAsync(userId, _environment->GetLexicalItem(user->language, "havenottokens"));
    TELEBOT_TASK(send);

    return false;
}