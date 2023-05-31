#include "MyBot.h"

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
    *_bot->OnCallbackQuery("back_settings_button_clicked") += THIS_METHOD_HANDLER(&MyBot::BackSettings);
    *_bot->OnCallbackQuery("gpt_context_size_button_clicked") += THIS_METHOD_HANDLER(&MyBot::SetContextSize);
    *_bot->OnCallbackQuery("gpt_temperature_button_clicked") += THIS_METHOD_HANDLER(&MyBot::SetGptTemperature);
    *_bot->OnCallbackQuery("gpt_allow_voice_button_clicked") += THIS_METHOD_HANDLER(&MyBot::SetGptAllowVoice);
    *_bot->OnCallbackQuery("whisper_temperature_button_clicked") += THIS_METHOD_HANDLER(&MyBot::SetWhisperTemperature);
    *_bot->OnCallbackQuery("dalle_size_button_clicked") += THIS_METHOD_HANDLER(&MyBot::SetDalleSize);
    *_bot->OnCallbackQuery("dalle_allow_voice_button_clicked") += THIS_METHOD_HANDLER(&MyBot::SetDalleAllowVoice);
    *_bot->OnCallbackQuery("english_button_clicked") += THIS_METHOD_HANDLER(&MyBot::SetEnglish);
    *_bot->OnCallbackQuery("russian_button_clicked") += THIS_METHOD_HANDLER(&MyBot::SetRussian);

    _bot->OnCallbackQuery("context_size_0_button_clicked",
                          [this](const Callback& callback){ SetContextSizeValue(callback, 0); });
    _bot->OnCallbackQuery("context_size_1_button_clicked",
                          [this](const Callback& callback){ SetContextSizeValue(callback, 1); });
    _bot->OnCallbackQuery("context_size_2_button_clicked",
                          [this](const Callback& callback){ SetContextSizeValue(callback, 2); });
    _bot->OnCallbackQuery("context_size_3_button_clicked",
                          [this](const Callback& callback){ SetContextSizeValue(callback, 3); });
    _bot->OnCallbackQuery("context_size_4_button_clicked",
                          [this](const Callback& callback){ SetContextSizeValue(callback, 4); });
    _bot->OnCallbackQuery("context_size_5_button_clicked",
                          [this](const Callback& callback){ SetContextSizeValue(callback, 5); });
    _bot->OnCallbackQuery("context_size_6_button_clicked",
                          [this](const Callback& callback){ SetContextSizeValue(callback, 6); });
    _bot->OnCallbackQuery("context_size_7_button_clicked",
                          [this](const Callback& callback){ SetContextSizeValue(callback, 7); });
    _bot->OnCallbackQuery("context_size_8_button_clicked",
                          [this](const Callback& callback){ SetContextSizeValue(callback, 8); });
    _bot->OnCallbackQuery("context_size_9_button_clicked",
                          [this](const Callback& callback){ SetContextSizeValue(callback, 9); });
    _bot->OnCallbackQuery("context_size_10_button_clicked",
                          [this](const Callback& callback){ SetContextSizeValue(callback, 10); });

    _bot->OnCallbackQuery("gpt_temperature_0_button_clicked",
                          [this](const Callback& callback){ SetGptTemperatureValue(callback, 0); });
    _bot->OnCallbackQuery("gpt_temperature_0.2_button_clicked",
                          [this](const Callback& callback){ SetGptTemperatureValue(callback, 0.2); });
    _bot->OnCallbackQuery("gpt_temperature_0.4_button_clicked",
                          [this](const Callback& callback){ SetGptTemperatureValue(callback, 0.4); });
    _bot->OnCallbackQuery("gpt_temperature_0.6_button_clicked",
                          [this](const Callback& callback){ SetGptTemperatureValue(callback, 0.6); });
    _bot->OnCallbackQuery("gpt_temperature_0.8_button_clicked",
                          [this](const Callback& callback){ SetGptTemperatureValue(callback, 0.8); });
    _bot->OnCallbackQuery("gpt_temperature_1_button_clicked",
                          [this](const Callback& callback){ SetGptTemperatureValue(callback, 1); });
    _bot->OnCallbackQuery("gpt_temperature_1.2_button_clicked",
                          [this](const Callback& callback){ SetGptTemperatureValue(callback, 1.2); });
    _bot->OnCallbackQuery("gpt_temperature_1.4_button_clicked",
                          [this](const Callback& callback){ SetGptTemperatureValue(callback, 1.4); });
    _bot->OnCallbackQuery("gpt_temperature_1.6_button_clicked",
                          [this](const Callback& callback){ SetGptTemperatureValue(callback, 1.6); });
    _bot->OnCallbackQuery("gpt_temperature_1.8_button_clicked",
                          [this](const Callback& callback){ SetGptTemperatureValue(callback, 1.8); });
    _bot->OnCallbackQuery("gpt_temperature_2_button_clicked",
                          [this](const Callback& callback){ SetGptTemperatureValue(callback, 2); });

    _bot->OnCallbackQuery("gpt_allow_voice_true_button_clicked",
                          [this](const Callback& callback){ SetGptAllowVoiceValue(callback, true); });
    _bot->OnCallbackQuery("gpt_allow_voice_false_button_clicked",
                          [this](const Callback& callback){ SetGptAllowVoiceValue(callback, false); });

    _bot->OnCallbackQuery("whisper_temperature_0_button_clicked",
                          [this](const Callback& callback){ SetWhisperTemperatureValue(callback, 0); });
    _bot->OnCallbackQuery("whisper_temperature_0.1_button_clicked",
                          [this](const Callback& callback){ SetWhisperTemperatureValue(callback, 0.2); });
    _bot->OnCallbackQuery("whisper_temperature_0.2_button_clicked",
                          [this](const Callback& callback){ SetWhisperTemperatureValue(callback, 0.2); });
    _bot->OnCallbackQuery("whisper_temperature_0.3_button_clicked",
                          [this](const Callback& callback){ SetWhisperTemperatureValue(callback, 0.3); });
    _bot->OnCallbackQuery("whisper_temperature_0.4_button_clicked",
                          [this](const Callback& callback){ SetWhisperTemperatureValue(callback, 0.4); });
    _bot->OnCallbackQuery("whisper_temperature_0.5_button_clicked",
                          [this](const Callback& callback){ SetWhisperTemperatureValue(callback, 0.5); });
    _bot->OnCallbackQuery("whisper_temperature_0.6_button_clicked",
                          [this](const Callback& callback){ SetWhisperTemperatureValue(callback, 0.6); });
    _bot->OnCallbackQuery("whisper_temperature_0.7_button_clicked",
                          [this](const Callback& callback){ SetWhisperTemperatureValue(callback, 0.7); });
    _bot->OnCallbackQuery("whisper_temperature_0.8_button_clicked",
                          [this](const Callback& callback){ SetWhisperTemperatureValue(callback, 0.8); });
    _bot->OnCallbackQuery("whisper_temperature_0.9_button_clicked",
                          [this](const Callback& callback){ SetWhisperTemperatureValue(callback, 0.9); });
    _bot->OnCallbackQuery("whisper_temperature_1_button_clicked",
                          [this](const Callback& callback){ SetWhisperTemperatureValue(callback, 1); });

    _bot->OnCallbackQuery("dalle_size_256x256_button_clicked",
                          [this](const Callback& callback){ SetDalleSizeValue(callback, OpenAI::Size::Mini); });
    _bot->OnCallbackQuery("dalle_size_512x512_button_clicked",
                          [this](const Callback& callback){ SetDalleSizeValue(callback, OpenAI::Size::Medium); });
    _bot->OnCallbackQuery("dalle_size_1024x1024_button_clicked",
                          [this](const Callback& callback){ SetDalleSizeValue(callback, OpenAI::Size::Large); });

    _bot->OnCallbackQuery("dalle_allow_voice_true_button_clicked",
                          [this](const Callback& callback){ SetDalleAllowVoiceValue(callback, true); });
    _bot->OnCallbackQuery("dalle_allow_voice_false_button_clicked",
                          [this](const Callback& callback){ SetDalleAllowVoiceValue(callback, false); });

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
    _bot->Stop();

    _openAiThreadsChecker.wait();
    _telebotThreadsChecker.wait();
    _dbThreadsChecker.wait();
    _commonChecker.wait();
}

void MyBot::MyBot::SetLogger(const std::string& logConfigPath)
{
    _logger = std::make_shared<CInfoLog::Logger>(logConfigPath);
}

void MyBot::MyBot::StartCommand(const Message& message)
{
    auto start = std::async(std::launch::async, [this, message]()
    {
        std::int64_t id = message->from->id;
        if (!_dbRequest->IsUser(id).get()) _dbRequest->AddUser(id).get();
        // TODO Hellow
        auto getUser = _dbCash->GetUserCash(id);
        auto getGptSettings = _dbCash->GetGptSettingsCash(id);
        auto getWhisperSettings = _dbCash->GetWhisperSettingsCash(id);
        auto getDalleSettings = _dbCash->GetDalleSettingsCash(id);
    });

    COMMON_TASK(start);
}

void MyBot::MyBot::GptSession(const Message& message)
{
    auto session = std::async(std::launch::async, [this, message]()
    {
        std::int64_t id = message->from->id;
        if (!_dbRequest->IsUser(id).get()) _dbRequest->AddUser(id).get();
        OpenAI::OpenAIModel::Ptr chatGpt = _openAI->GptTurboSession(std::to_string(id), OPENAI_USER);

        if (_openAiSessions.find(id) == _openAiSessions.end()) _openAiSessions.insert(std::make_pair(id, chatGpt));
        else _openAiSessions[id] = chatGpt;

        GptSettings::Ptr settings = _dbCash->GetGptSettingsCash(id);
        std::shared_ptr<OpenAI::GptTurbo> gptTurboPtr = std::dynamic_pointer_cast<OpenAI::GptTurbo>(_openAiSessions[id]);
        gptTurboPtr->SetContextSize(settings->contextsize);
        gptTurboPtr->SetTemperature(settings->temperature);
        gptTurboPtr->AllowModelMessagesInContext(settings->allowvoice);

        InlineButton helpButton = INLINE_BUTTON(LEXICAL_ITEM("helpinline"), "gpt_help_button_clicked");
        InlineButton settingsButton = INLINE_BUTTON(LEXICAL_ITEM("settingsinline"), "gpt_settings_button_clicked");

        Telebot::InlineKeyboardMarkup::Ptr keyboard = std::make_shared<Telebot::InlineKeyboardMarkup>();
        keyboard->SetButton(helpButton, 0, 0);
        keyboard->SetButton(settingsButton, 0, 1);

        auto send = _bot->SendMessageAsync(id, LEXICAL_ITEM("gpthellow"), keyboard);
        TELEBOT_TASK(send);
    });

    COMMON_TASK(session);
}

void MyBot::MyBot::WhisperSession(const Message& message)
{
    auto session = std::async(std::launch::async, [this, message]()
    {
        std::int64_t id = message->from->id;
        if (!_dbRequest->IsUser(id).get()) _dbRequest->AddUser(id).get();
        OpenAI::OpenAIModel::Ptr whisper = _openAI->WhisperSession();

        if (_openAiSessions.find(id) == _openAiSessions.end()) _openAiSessions.insert(std::make_pair(id, whisper));
        else _openAiSessions[id] = whisper;

        WhisperSettings::Ptr settings = _dbCash->GetWhisperSettingsCash(id);
        std::shared_ptr<OpenAI::Whisper> whisperPtr = std::dynamic_pointer_cast<OpenAI::Whisper>(_openAiSessions[id]);
        whisperPtr->SetTemperature(settings->temperature);

        InlineButton helpButton = INLINE_BUTTON(LEXICAL_ITEM("helpinline"), "whisper_help_button_clicked");
        InlineButton settingsButton = INLINE_BUTTON(LEXICAL_ITEM("settingsinline"), "whisper_settings_button_clicked");

        Telebot::InlineKeyboardMarkup::Ptr keyboard = std::make_shared<Telebot::InlineKeyboardMarkup>();
        keyboard->SetButton(helpButton, 0, 0);
        keyboard->SetButton(settingsButton, 0, 1);

        auto send = _bot->SendMessageAsync(id, LEXICAL_ITEM("whisperhellow"), keyboard);
        TELEBOT_TASK(send);
    });

    COMMON_TASK(session);
}

void MyBot::MyBot::DalleSession(const Message& message)
{
    auto session = std::async(std::launch::async, [this, message]()
    {
        std::int64_t id = message->from->id;
        if (!_dbRequest->IsUser(id).get()) _dbRequest->AddUser(id).get();
        OpenAI::OpenAIModel::Ptr dalle = _openAI->DalleSession(std::to_string(id));

        if (_openAiSessions.find(id) == _openAiSessions.end()) _openAiSessions.insert(std::make_pair(id, dalle));
        else _openAiSessions[id] = dalle;

        DalleSettings::Ptr settings = _dbCash->GetDalleSettingsCash(id);
        std::shared_ptr<OpenAI::Dalle> dallePtr = std::dynamic_pointer_cast<OpenAI::Dalle>(_openAiSessions[id]);
        dallePtr->SetSize(settings->size);

        InlineButton helpButton = INLINE_BUTTON(LEXICAL_ITEM("helpinline"), "dalle_help_button_clicked");
        InlineButton settingsButton = INLINE_BUTTON(LEXICAL_ITEM("settingsinline"), "dalle_settings_button_clicked");

        Telebot::InlineKeyboardMarkup::Ptr keyboard = std::make_shared<Telebot::InlineKeyboardMarkup>();
        keyboard->SetButton(helpButton, 0, 0);
        keyboard->SetButton(settingsButton, 0, 1);

        auto send = _bot->SendMessageAsync(id, LEXICAL_ITEM("dallehellow"), keyboard);
        TELEBOT_TASK(send);
    });

    COMMON_TASK(session);
}

void MyBot::MyBot::GetUsageInfo(const Message& message)
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
        TELEBOT_TASK(send);
    });

    COMMON_TASK(get);
}

void MyBot::MyBot::GetPayment(const Message& message)
{
    auto get = std::async(std::launch::async, [this, message]()
    {
        std::int64_t id = message->from->id;
        if (!_dbRequest->IsUser(id).get()) _dbRequest->AddUser(id).get();
        // TODO GetPayment
        auto send = _bot->SendMessageAsync(id, "get_payment_command_invoked");
        TELEBOT_TASK(send);
    });

    COMMON_TASK(get);
}

void MyBot::MyBot::GetHelp(const Message& message)
{
    auto get = std::async(std::launch::async, [this, message]()
    {
        std::int64_t id = message->from->id;
        if (!_dbRequest->IsUser(id).get()) _dbRequest->AddUser(id).get();

        InlineButton gptHelpButton = INLINE_BUTTON("gpt", "gpt_help_button_clicked");
        InlineButton whisperHelpButton = INLINE_BUTTON("whisper", "whisper_help_button_clicked");
        InlineButton dalleHelpButton = INLINE_BUTTON("dalle", "dalle_help_button_clicked");

        Telebot::InlineKeyboardMarkup::Ptr keyboard = std::make_shared<Telebot::InlineKeyboardMarkup>();
        keyboard->SetButton(gptHelpButton, 0, 0);
        keyboard->SetButton(whisperHelpButton, 0, 1);
        keyboard->SetButton(dalleHelpButton, 0, 2);

        auto send = _bot->SendMessageAsync(id, LEXICAL_ITEM("gethelp"), keyboard);
        TELEBOT_TASK(send);
    });

    COMMON_TASK(get);
}

void MyBot::MyBot::SetSettings(const Message& message)
{
    auto set = std::async(std::launch::async, [this, message]()
    {
        std::int64_t id = message->from->id;
        if (!_dbRequest->IsUser(id).get()) _dbRequest->AddUser(id).get();

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
        TELEBOT_TASK(send);
    });

    COMMON_TASK(set);
}

void MyBot::MyBot::GetGptHelp(const Callback& callback)
{
    auto asyncCallback = std::async(std::launch::async, [this, callback]()
    {
        std::int64_t id = callback->from->id;
        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);

        auto send = _bot->SendMessageAsync(id, LEXICAL_ITEM("gpthelp"));
        TELEBOT_TASK(send);
    });

    COMMON_TASK(asyncCallback);
}

void MyBot::MyBot::GetWhisperHelp(const Callback& callback)
{
    auto asyncCallback = std::async(std::launch::async, [this, callback]()
    {
        std::int64_t id = callback->from->id;
        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);

        auto send = _bot->SendMessageAsync(id, LEXICAL_ITEM("whisperhelp"));
        TELEBOT_TASK(send);
    });

    COMMON_TASK(asyncCallback);
}

void MyBot::MyBot::GetDalleHelp(const Callback& callback)
{
    auto asyncCallback = std::async(std::launch::async, [this, callback]()
    {
        std::int64_t id = callback->from->id;
        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);

        auto send = _bot->SendMessageAsync(id, LEXICAL_ITEM("dallehelp"));
        TELEBOT_TASK(send);
    });

    COMMON_TASK(asyncCallback);
}

void MyBot::MyBot::SetGptSettings(const Callback& callback)
{
    auto asyncCallback = std::async(std::launch::async, [this, callback]()
    {
        std::int64_t id = callback->from->id;
        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);

        InlineButton backButton = INLINE_BUTTON(LEXICAL_ITEM("settingsinline"), "back_settings_button_clicked");
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
    });

    COMMON_TASK(asyncCallback);
}

void MyBot::MyBot::SetWhisperSettings(const Callback& callback)
{
    auto asyncCallback = std::async(std::launch::async, [this, callback]()
    {
        std::int64_t id = callback->from->id;
        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);

        InlineButton backButton = INLINE_BUTTON(LEXICAL_ITEM("settingsinline"), "back_settings_button_clicked");
        InlineButton temperatureButton = INLINE_BUTTON(LEXICAL_ITEM("temperatureinline"), "whisper_temperature_button_clicked");

        Telebot::InlineKeyboardMarkup::Ptr keyboard = std::make_shared<Telebot::InlineKeyboardMarkup>();
        keyboard->SetButton(backButton, 0, 0);
        keyboard->SetButton(temperatureButton, 0, 1);

        auto send = _bot->EditMessageTextAsync(id, callback->message->message_id, LEXICAL_ITEM("whispersettings"), keyboard);
        TELEBOT_TASK(send);
    });

    COMMON_TASK(asyncCallback);
}

void MyBot::MyBot::SetDalleSettings(const Callback& callback)
{
    auto asyncCallback = std::async(std::launch::async, [this, callback]()
    {
        std::int64_t id = callback->from->id;
        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);

        InlineButton backButton = INLINE_BUTTON(LEXICAL_ITEM("settingsinline"), "back_settings_button_clicked");
        InlineButton sizeButton = INLINE_BUTTON(LEXICAL_ITEM("sizeinline"), "dalle_size_button_clicked");
        InlineButton allowVoiceButton = INLINE_BUTTON(LEXICAL_ITEM("allowvoiceinline"), "dalle_allow_voice_button_clicked");

        Telebot::InlineKeyboardMarkup::Ptr keyboard = std::make_shared<Telebot::InlineKeyboardMarkup>();
        keyboard->SetButton(backButton, 0, 0);
        keyboard->SetButton(sizeButton, 0, 1);
        keyboard->SetButton(allowVoiceButton, 1, 0);

        auto send = _bot->EditMessageTextAsync(id, callback->message->message_id, LEXICAL_ITEM("dallesettings"), keyboard);
        TELEBOT_TASK(send);
    });

    COMMON_TASK(asyncCallback);
}

void MyBot::MyBot::SetLanguage(const Callback& callback)
{
    auto asyncCallback = std::async(std::launch::async, [this, callback]()
    {
        std::int64_t id = callback->from->id;
        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);

        InlineButton backButton = INLINE_BUTTON(LEXICAL_ITEM("settingsinline"), "back_settings_button_clicked");
        InlineButton englishButton = INLINE_BUTTON("English", "english_button_clicked");
        InlineButton russianButton = INLINE_BUTTON("Русский", "russian_button_clicked");

        Telebot::InlineKeyboardMarkup::Ptr keyboard = std::make_shared<Telebot::InlineKeyboardMarkup>();
        keyboard->SetButton(backButton, 0, 0);
        keyboard->SetButton(englishButton, 0, 1);
        keyboard->SetButton(russianButton, 0, 2);

        auto send = _bot->EditMessageTextAsync(id, callback->message->message_id, LEXICAL_ITEM("choicelanguage"), keyboard);
        TELEBOT_TASK(send);
    });

    COMMON_TASK(asyncCallback);
}

void MyBot::MyBot::BackSettings(const Callback& callback)
{
    auto back = std::async(std::launch::async, [this, callback]()
    {
        std::int64_t id = callback->from->id;
        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);

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
    });

    COMMON_TASK(back);
}

void MyBot::MyBot::SetContextSize(const Callback& callback)
{
    auto asyncCallback = std::async(std::launch::async, [this, callback]()
    {
        std::int64_t id = callback->from->id;
        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);

        InlineButton backButton = INLINE_BUTTON("<<", "gpt_settings_button_clicked");
        InlineButton contextSize0 = INLINE_BUTTON("0", "context_size_0_button_clicked");
        InlineButton contextSize1 = INLINE_BUTTON("1", "context_size_1_button_clicked");
        InlineButton contextSize2 = INLINE_BUTTON("2", "context_size_2_button_clicked");
        InlineButton contextSize3 = INLINE_BUTTON("3", "context_size_3_button_clicked");
        InlineButton contextSize4 = INLINE_BUTTON("4", "context_size_4_button_clicked");
        InlineButton contextSize5 = INLINE_BUTTON("5", "context_size_5_button_clicked");
        InlineButton contextSize6 = INLINE_BUTTON("6", "context_size_6_button_clicked");
        InlineButton contextSize7 = INLINE_BUTTON("7", "context_size_7_button_clicked");
        InlineButton contextSize8 = INLINE_BUTTON("8", "context_size_8_button_clicked");
        InlineButton contextSize9 = INLINE_BUTTON("9", "context_size_9_button_clicked");
        InlineButton contextSize10 = INLINE_BUTTON("10", "context_size_10_button_clicked");

        Telebot::InlineKeyboardMarkup::Ptr keyboard = std::make_shared<Telebot::InlineKeyboardMarkup>();
        keyboard->SetButton(backButton, 0, 0);
        keyboard->SetButton(contextSize0, 0, 1);
        keyboard->SetButton(contextSize1, 0, 2);
        keyboard->SetButton(contextSize2, 0, 3);
        keyboard->SetButton(contextSize3, 1, 0);
        keyboard->SetButton(contextSize4, 1, 1);
        keyboard->SetButton(contextSize5, 1, 2);
        keyboard->SetButton(contextSize6, 1, 3);
        keyboard->SetButton(contextSize7, 2, 0);
        keyboard->SetButton(contextSize8, 2, 1);
        keyboard->SetButton(contextSize9, 2, 2);
        keyboard->SetButton(contextSize10, 2, 3);

        auto send = _bot->EditMessageTextAsync(id, callback->message->message_id,
                                               LEXICAL_ITEM("contextsize") + std::to_string(_dbCash->GetGptSettingsCash(id)->contextsize), keyboard);
        TELEBOT_TASK(send);
    });

    COMMON_TASK(asyncCallback);
}

void MyBot::MyBot::SetGptTemperature(const Callback& callback)
{
    auto asyncCallback = std::async(std::launch::async, [this, callback]()
    {
        std::int64_t id = callback->from->id;
        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);

        InlineButton backButton = INLINE_BUTTON("<<", "gpt_settings_button_clicked");
        InlineButton gptTemperature0 = INLINE_BUTTON("0", "gpt_temperature_0_button_clicked");
        InlineButton gptTemperature02 = INLINE_BUTTON("0.2", "gpt_temperature_0.2_button_clicked");
        InlineButton gptTemperature04 = INLINE_BUTTON("0.4", "gpt_temperature_0.4_button_clicked");
        InlineButton gptTemperature06 = INLINE_BUTTON("0.6", "gpt_temperature_0.6_button_clicked");
        InlineButton gptTemperature08 = INLINE_BUTTON("0.8", "gpt_temperature_0.8_button_clicked");
        InlineButton gptTemperature10 = INLINE_BUTTON("1", "gpt_temperature_1_button_clicked");
        InlineButton gptTemperature12 = INLINE_BUTTON("1.2", "gpt_temperature_1.2_button_clicked");
        InlineButton gptTemperature14 = INLINE_BUTTON("1.4", "gpt_temperature_1.4_button_clicked");
        InlineButton gptTemperature16 = INLINE_BUTTON("1.6", "gpt_temperature_1.6_button_clicked");
        InlineButton gptTemperature18 = INLINE_BUTTON("1.8", "gpt_temperature_1.8_button_clicked");
        InlineButton gptTemperature20 = INLINE_BUTTON("2", "gpt_temperature_2_button_clicked");

        Telebot::InlineKeyboardMarkup::Ptr keyboard = std::make_shared<Telebot::InlineKeyboardMarkup>();
        keyboard->SetButton(backButton, 0, 0);
        keyboard->SetButton(gptTemperature0, 0, 1);
        keyboard->SetButton(gptTemperature02, 0, 2);
        keyboard->SetButton(gptTemperature04, 0, 3);
        keyboard->SetButton(gptTemperature06, 1, 0);
        keyboard->SetButton(gptTemperature08, 1, 1);
        keyboard->SetButton(gptTemperature10, 1, 2);
        keyboard->SetButton(gptTemperature12, 1, 3);
        keyboard->SetButton(gptTemperature14, 2, 0);
        keyboard->SetButton(gptTemperature16, 2, 1);
        keyboard->SetButton(gptTemperature18, 2, 2);
        keyboard->SetButton(gptTemperature20, 2, 3);

        auto send = _bot->EditMessageTextAsync(id, callback->message->message_id,
                                               LEXICAL_ITEM("gpttemperature") + std::to_string(_dbCash->GetGptSettingsCash(id)->temperature), keyboard);
        TELEBOT_TASK(send);
    });

    COMMON_TASK(asyncCallback);
}

void MyBot::MyBot::SetGptAllowVoice(const Callback& callback)
{
    auto asyncCallback = std::async(std::launch::async, [this, callback]()
    {
        std::int64_t id = callback->from->id;
        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);

        InlineButton backButton = INLINE_BUTTON("<<", "gpt_settings_button_clicked");
        InlineButton gptAllowVoiceTrue = INLINE_BUTTON("true", "gpt_allow_voice_true_button_clicked");
        InlineButton gptAllowVoiceFalse = INLINE_BUTTON("false", "gpt_allow_voice_false_button_clicked");

        Telebot::InlineKeyboardMarkup::Ptr keyboard = std::make_shared<Telebot::InlineKeyboardMarkup>();
        keyboard->SetButton(backButton, 0, 0);
        keyboard->SetButton(gptAllowVoiceTrue, 0, 1);
        keyboard->SetButton(gptAllowVoiceFalse, 0, 2);

        auto send = _bot->EditMessageTextAsync(id, callback->message->message_id,
                                               LEXICAL_ITEM("allowvoice") + LEXICAL_ITEM(ToString(_dbCash->GetGptSettingsCash(id)->allowvoice)), keyboard);
        TELEBOT_TASK(send);
    });

    COMMON_TASK(asyncCallback);
}

void MyBot::MyBot::SetWhisperTemperature(const Callback& callback)
{
    auto asyncCallback = std::async(std::launch::async, [this, callback]()
    {
        std::int64_t id = callback->from->id;
        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);

        InlineButton backButton = INLINE_BUTTON("<<", "whisper_settings_button_clicked");
        InlineButton whisperTemperature0 = INLINE_BUTTON("0", "whisper_temperature_0_button_clicked");
        InlineButton whisperTemperature01 = INLINE_BUTTON("0.1", "whisper_temperature_0.1_button_clicked");
        InlineButton whisperTemperature02 = INLINE_BUTTON("0.2", "whisper_temperature_0.2_button_clicked");
        InlineButton whisperTemperature03 = INLINE_BUTTON("0.3", "whisper_temperature_0.3_button_clicked");
        InlineButton whisperTemperature04 = INLINE_BUTTON("0.4", "whisper_temperature_0.4_button_clicked");
        InlineButton whisperTemperature05 = INLINE_BUTTON("0.5", "whisper_temperature_0.5_button_clicked");
        InlineButton whisperTemperature06 = INLINE_BUTTON("0.6", "whisper_temperature_0.6_button_clicked");
        InlineButton whisperTemperature07 = INLINE_BUTTON("0.7", "whisper_temperature_0.7_button_clicked");
        InlineButton whisperTemperature08 = INLINE_BUTTON("0.8", "whisper_temperature_0.8_button_clicked");
        InlineButton whisperTemperature09 = INLINE_BUTTON("0.9", "whisper_temperature_0.9_button_clicked");
        InlineButton whisperTemperature10 = INLINE_BUTTON("1", "whisper_temperature_1_button_clicked");

        Telebot::InlineKeyboardMarkup::Ptr keyboard = std::make_shared<Telebot::InlineKeyboardMarkup>();
        keyboard->SetButton(backButton, 0, 0);
        keyboard->SetButton(whisperTemperature0, 0, 1);
        keyboard->SetButton(whisperTemperature01, 0, 2);
        keyboard->SetButton(whisperTemperature02, 0, 3);
        keyboard->SetButton(whisperTemperature03, 1, 0);
        keyboard->SetButton(whisperTemperature04, 1, 1);
        keyboard->SetButton(whisperTemperature05, 1, 2);
        keyboard->SetButton(whisperTemperature06, 1, 3);
        keyboard->SetButton(whisperTemperature07, 2, 0);
        keyboard->SetButton(whisperTemperature08, 2, 1);
        keyboard->SetButton(whisperTemperature09, 2, 2);
        keyboard->SetButton(whisperTemperature10, 2, 3);

        auto send = _bot->EditMessageTextAsync(id, callback->message->message_id,
                                               LEXICAL_ITEM("whispertemperature") + std::to_string(_dbCash->GetWhisperSettingsCash(id)->temperature), keyboard);
        TELEBOT_TASK(send);
    });

    COMMON_TASK(asyncCallback);
}

void MyBot::MyBot::SetDalleSize(const Callback& callback)
{
    auto asyncCallback = std::async(std::launch::async, [this, callback]()
    {
        std::int64_t id = callback->from->id;
        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);

        InlineButton backButton = INLINE_BUTTON("<<", "dalle_settings_button_clicked");
        InlineButton miniSize = INLINE_BUTTON("256x256", "dalle_size_256x256_button_clicked");
        InlineButton mediumSize = INLINE_BUTTON("512x512", "dalle_size_512x512_button_clicked");
        InlineButton largeSize = INLINE_BUTTON("1024x1024", "dalle_size_1024x1024_button_clicked");

        Telebot::InlineKeyboardMarkup::Ptr keyboard = std::make_shared<Telebot::InlineKeyboardMarkup>();
        keyboard->SetButton(backButton, 0, 0);
        keyboard->SetButton(miniSize, 0, 1);
        keyboard->SetButton(mediumSize, 1, 0);
        keyboard->SetButton(largeSize, 1, 1);

        auto send = _bot->EditMessageTextAsync(id, callback->message->message_id,
                                               LEXICAL_ITEM("dallesize") + ToString(_dbCash->GetDalleSettingsCash(id)->size), keyboard);
        TELEBOT_TASK(send);
    });

    COMMON_TASK(asyncCallback);
}

void MyBot::MyBot::SetDalleAllowVoice(const Callback& callback)
{
    auto asyncCallback = std::async(std::launch::async, [this, callback]()
    {
        std::int64_t id = callback->from->id;
        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);

        InlineButton backButton = INLINE_BUTTON("<<", "dalle_settings_button_clicked");
        InlineButton dalleAllowVoiceTrue = INLINE_BUTTON("true", "dalle_allow_voice_true_button_clicked");
        InlineButton dalleAllowVoiceFalse = INLINE_BUTTON("false", "dalle_allow_voice_false_button_clicked");

        Telebot::InlineKeyboardMarkup::Ptr keyboard = std::make_shared<Telebot::InlineKeyboardMarkup>();
        keyboard->SetButton(backButton, 0, 0);
        keyboard->SetButton(dalleAllowVoiceTrue, 0, 1);
        keyboard->SetButton(dalleAllowVoiceFalse, 0, 2);

        auto send = _bot->EditMessageTextAsync(id, callback->message->message_id,
                                               LEXICAL_ITEM("allowvoice") + LEXICAL_ITEM(ToString(_dbCash->GetDalleSettingsCash(id)->allowvoice)), keyboard);
        TELEBOT_TASK(send);
    });

    COMMON_TASK(asyncCallback);
}

void MyBot::MyBot::SetEnglish(const Callback& callback)
{
    auto set = std::async(std::launch::async, [this, callback]()
    {
        std::int64_t id = callback->from->id;
        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);

        auto updateDb = _dbCash->SetLanguageCash(id, Language::English);
        DB_TASK(updateDb);

        auto send = _bot->SendMessageAsync(id, LEXICAL_ITEM("setenglishcompleted"));
        TELEBOT_TASK(send);
    });

    COMMON_TASK(set);
}

void MyBot::MyBot::SetRussian(const Callback& callback)
{
    auto set = std::async(std::launch::async, [this, callback]()
    {
        std::int64_t id = callback->from->id;
        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);

        auto updateDb = _dbCash->SetLanguageCash(id, Language::Russian);
        DB_TASK(updateDb);

        auto send = _bot->SendMessageAsync(id, LEXICAL_ITEM("setrussiancompleted"));
        TELEBOT_TASK(send);
    });

    COMMON_TASK(set);
}

void MyBot::MyBot::Chat(const Message& message)
{
    std::int64_t id = message->from->id;
    if (_openAiSessions.find(id) == _openAiSessions.end() || _openAiSessions[id]->GetModelName() != "gpt-3.5-turbo") return;

    std::future<bool> chat = AddToQueue<bool>([this](const OpenAI::OpenAIModel::Ptr& model,
                                                     const Message& message)->bool
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

void MyBot::MyBot::Transcript(const Message& message)
{
    std::int64_t id = message->from->id;
    if (_openAiSessions.find(id) == _openAiSessions.end() || _openAiSessions[id]->GetModelName() != "whisper-1") return;

    std::future<bool> transcript = AddToQueue<bool>([this](const OpenAI::OpenAIModel::Ptr& model,
                                                           const Message& message)->bool
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

void MyBot::MyBot::CreateImage(const Message& message)
{
    std::int64_t id = message->from->id;
    if (_openAiSessions.find(id) == _openAiSessions.end() || _openAiSessions[id]->GetModelName() != "DALLE") return;

    std::future<bool> create = AddToQueue<bool>([this](const OpenAI::OpenAIModel::Ptr& model,
                                                       const Message& message)->bool
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

void MyBot::MyBot::SetContextSizeValue(const Callback& callback, unsigned char contextSize)
{
    auto set = std::async(std::launch::async, [this, callback](unsigned char contextSize)
    {
        std::int64_t id = callback->from->id;
        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);

        auto updateDb = _dbCash->SetContextSizeCash(id, contextSize);
        DB_TASK(updateDb);

        auto send = _bot->SendMessageAsync(id, LEXICAL_ITEM("setcontextsizecomplited") + std::to_string(contextSize));
        TELEBOT_TASK(send);

        if (_openAiSessions.find(id) == _openAiSessions.end() || _openAiSessions[id]->GetModelName() != "gpt-3.5-turbo") return;
        std::shared_ptr<OpenAI::GptTurbo> gptTurbo = std::dynamic_pointer_cast<OpenAI::GptTurbo>(_openAiSessions[id]);
        gptTurbo->SetContextSize(contextSize);
    }, contextSize);

    COMMON_TASK(set);
}

void MyBot::MyBot::SetGptTemperatureValue(const Callback& callback, float temperature)
{
    auto set = std::async(std::launch::async, [this, callback](float temperature)
    {
        std::int64_t id = callback->from->id;
        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);

        auto updateDb = _dbCash->SetGptTemperatureCash(id, temperature);
        DB_TASK(updateDb);

        auto send = _bot->SendMessageAsync(id, LEXICAL_ITEM("settemperaturecomplited") + std::to_string(temperature));
        TELEBOT_TASK(send);

        if (_openAiSessions.find(id) == _openAiSessions.end() || _openAiSessions[id]->GetModelName() != "gpt-3.5-turbo") return;
        std::shared_ptr<OpenAI::GptTurbo> gptTurbo = std::dynamic_pointer_cast<OpenAI::GptTurbo>(_openAiSessions[id]);
        gptTurbo->SetTemperature(temperature);
    }, temperature);

    COMMON_TASK(set);
}

void MyBot::MyBot::SetGptAllowVoiceValue(const Callback& callback, bool allowVoice)
{
    auto set = std::async(std::launch::async, [this, callback](bool allowVoice)
    {
        std::int64_t id = callback->from->id;
        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);

        auto updateDb = _dbCash->SetGptAllowVoiceCash(id, allowVoice);
        DB_TASK(updateDb);

        auto send = _bot->SendMessageAsync(id, LEXICAL_ITEM("setallowvoicecomplited") + LEXICAL_ITEM(ToString(allowVoice)));
        TELEBOT_TASK(send);

        if (_openAiSessions.find(id) == _openAiSessions.end() || _openAiSessions[id]->GetModelName() != "gpt-3.5-turbo") return;
        // TODO GPT allow voice
    }, allowVoice);

    COMMON_TASK(set);
}

void MyBot::MyBot::SetWhisperTemperatureValue(const Callback& callback, float temperature)
{
    auto set = std::async(std::launch::async, [this, callback](float temperature)
    {
        std::int64_t id = callback->from->id;
        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);

        auto updateDb = _dbCash->SetWhisperTemperatureCash(id, temperature);
        DB_TASK(updateDb);

        auto send = _bot->SendMessageAsync(id, LEXICAL_ITEM("settemperaturecomplited") + std::to_string(temperature));
        TELEBOT_TASK(send);

        if (_openAiSessions.find(id) == _openAiSessions.end() || _openAiSessions[id]->GetModelName() != "whisper-1") return;
        std::shared_ptr<OpenAI::Whisper> whisper = std::dynamic_pointer_cast<OpenAI::Whisper>(_openAiSessions[id]);
        whisper->SetTemperature(temperature);
    }, temperature);

    COMMON_TASK(set);
}

void MyBot::MyBot::SetDalleSizeValue(const Callback& callback, OpenAI::Size size)
{
    auto set = std::async(std::launch::async, [this, callback](OpenAI::Size size)
    {
        std::int64_t id = callback->from->id;
        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);

        auto updateDb = _dbCash->SetDalleSizeCash(id, size);
        DB_TASK(updateDb);

        auto send = _bot->SendMessageAsync(id, LEXICAL_ITEM("setdallesizecomplited") + OpenAI::ToString(size));
        TELEBOT_TASK(send);

        if (_openAiSessions.find(id) == _openAiSessions.end() || _openAiSessions[id]->GetModelName() != "DALLE") return;
        std::shared_ptr<OpenAI::Dalle> dalle = std::dynamic_pointer_cast<OpenAI::Dalle>(_openAiSessions[id]);
        dalle->SetSize(size);
    }, size);

    COMMON_TASK(set);
}

void MyBot::MyBot::SetDalleAllowVoiceValue(const Callback& callback, bool allowVoice)
{
    auto set = std::async(std::launch::async, [this, callback](bool allowVoice)
    {
        std::int64_t id = callback->from->id;
        auto answer = _bot->AnswerCallbackQueryAsync(callback->id);

        auto updateDb = _dbCash->SetDalleAllowVoiceCash(id, allowVoice);
        DB_TASK(updateDb);

        auto send = _bot->SendMessageAsync(id, LEXICAL_ITEM("setallowvoicecomplited") + LEXICAL_ITEM(ToString(allowVoice)));
        TELEBOT_TASK(send);

        if (_openAiSessions.find(id) == _openAiSessions.end() || _openAiSessions[id]->GetModelName() != "DALLE") return;
        // TODO Dalle allow voice
    }, allowVoice);

    COMMON_TASK(set);
}