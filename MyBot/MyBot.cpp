#include "MyBot.h"

const std::string MyBot::MyBot::FILE_DIRECTORY = "root/files";
const unsigned char MyBot::MyBot::POOL_MAX_SIZE = 3;
const std::string MyBot::MyBot::LOG_CONFIG_PATH = "LogConfig.xml";
const std::string MyBot::MyBot::OPENAI_USER = "TelegramBot";
const unsigned short MyBot::MyBot::REQUESTS_PER_MINUTE_LIMIT = 3;

MyBot::MyBot::MyBot(const std::string& botToken, const std::string& openAIToken, const std::string& dbConnectionString)
{
    _bot = std::make_unique<Telebot::Telebot>(botToken);
    _openAI = std::make_unique<OpenAI::OpenAI>(openAIToken);
    _dbConnection = std::make_unique<DbProvider::DbConnection>(dbConnectionString, POOL_MAX_SIZE);
    auto factory = CInfoLog::LoggerFactory(LOG_CONFIG_PATH);
    _logger = factory.CreateLogger();
    _requestsPerLastMinute = 0;

    *_bot->OnCommand("gpt") += THIS_METHOD_HANDLER(&MyBot::GptSession)
    *_bot->OnCommand("whisper") += THIS_METHOD_HANDLER(&MyBot::WhisperSession)
    *_bot->OnCommand("usage") += THIS_METHOD_HANDLER(&MyBot::GetUsageInfo)
    *_bot->OnAnyMessage() += THIS_METHOD_HANDLER(&MyBot::Chat)
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

std::future<unsigned short> MyBot::MyBot::GetContextLimit(std::int64_t userId)
{
    std::function<unsigned short(pqxx::work&, std::int64_t)> transaction =
            [](pqxx::work& work, const std::int64_t& userId)->unsigned short
            {
                std::string query = "SELECT contextlimit FROM \"Users\" WHERE userid = " + std::to_string(userId);
                return work.query_value<unsigned short>(query);
            };

    return _dbConnection->TransactAsync<unsigned short, std::int64_t>(transaction, userId);
}

std::future<bool> MyBot::MyBot::SetContextLimit(std::int64_t userId, unsigned short contextLimit)
{
    std::function<bool(pqxx::work&, std::int64_t, unsigned short)> transaction =
            [](pqxx::work& work, const std::int64_t& userId, const unsigned short& contextLimit)->bool
            {
                std::string query = "UPDATE \"Users\" SET contextlimit = " + std::to_string(contextLimit) +
                                    " WHERE userid = " + std::to_string(userId);
                work.exec(query);
                return true;
            };

    return _dbConnection->TransactAsync<bool, std::int64_t, unsigned short>(transaction, userId, contextLimit);
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

void MyBot::MyBot::Accept()
{
    std::vector<std::pair<std::string, std::string>> commands;
    commands.emplace_back("gpt", "start chat gpt session");
    commands.emplace_back("whisper", "start transcribe audio");
    commands.emplace_back("usage", "get information about available tokens");
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

void MyBot::MyBot::WhisperSession(const Telebot::Message::Ptr& message)
{
    auto session = std::async(std::launch::async, [this, message]()
    {
        std::int64_t id = message->from->id;
        if (!IsUser(id).get()) AddUser(id).get();
        OpenAI::OpenAiModel::Ptr whisper = _openAI->WhisperSession();

        if (_openAiSessions.find(id) == _openAiSessions.end()) _openAiSessions.insert(std::make_pair(id, whisper));
        else _openAiSessions[id] = whisper;

        auto send = _bot->SendMessageAsync(id, "Hello! I can translate audio.");
        TELEBOT_TASK(send)
    });

    COMMON_TASK(session)
}

void MyBot::MyBot::GptSession(const Telebot::Message::Ptr& message)
{
    auto session = std::async(std::launch::async, [this, message]()
    {
        std::int64_t id = message->from->id;
        if (!IsUser(id).get()) AddUser(id).get();
        OpenAI::OpenAiModel::Ptr chatGpt = _openAI->GptTurboSession(std::to_string(id), OPENAI_USER, OpenAI::Role::User);

        if (_openAiSessions.find(id) == _openAiSessions.end()) _openAiSessions.insert(std::make_pair(id, chatGpt));
        else _openAiSessions[id] = chatGpt;

        auto send = _bot->SendMessageAsync(id, "Hello! How can I assist you today?");
        TELEBOT_TASK(send)
    });

    COMMON_TASK(session)
}

void MyBot::MyBot::GetUsageInfo(const Telebot::Message::Ptr& message)
{
    auto get = std::async(std::launch::async, [this, message]()
    {
        std::int64_t id = message->from->id;

        std::future<int> totalUsageFuture = GetUsage(id);
        std::future<int> usageLimitFuture = GetUsageLimit(id);

        int totalUsage = totalUsageFuture.get();
        int usageLimit = usageLimitFuture.get();

        auto send = _bot->SendMessageAsync(id, "You have " + std::to_string(usageLimit - totalUsage) + " tokens.");
        TELEBOT_TASK(send)
    });

    COMMON_TASK(get)
}

void MyBot::MyBot::Chat(const Telebot::Message::Ptr& message)
{
    std::int64_t id = message->from->id;
    if (_openAiSessions.find(id) == _openAiSessions.end() || _openAiSessions[id]->GetModelName() != "gpt-3.5-turbo") return;

    std::future<bool> chat = AddToQueue<bool>([this](const OpenAI::OpenAiModel::Ptr& model,
                                                     const Telebot::Message::Ptr& message)->bool
    {
        std::int64_t id = message->from->id;
        std::shared_ptr<OpenAI::GptTurbo> gptTurbo = std::dynamic_pointer_cast<OpenAI::GptTurbo>(_openAiSessions[id]);
        if (gptTurbo == nullptr || !UserHasTokens(id)) return false;

        std::pair<std::string, int> answer = gptTurbo->Chat(message->text);

        auto addUsage = AddUsage(id, answer.second);
        DB_TASK(addUsage)

        auto send = _bot->SendMessageAsync(id, answer.first);
        TELEBOT_TASK(send)

        return true;
    }, _openAiSessions[id], message);

    OPENAI_TASK(chat)
}

void MyBot::MyBot::Transcript(const Telebot::Message::Ptr& message)
{
    std::int64_t id = message->from->id;
    if (_openAiSessions.find(id) == _openAiSessions.end() || _openAiSessions[id]->GetModelName() != "whisper-1") return;

    std::future<bool> transcript = AddToQueue<bool>([this](const OpenAI::OpenAiModel::Ptr& model,
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

        auto onLoad = _bot->LoadFileAsync(message->voice->file_id, directory);
        std::string filePath = onLoad.get();
        ConvertAudio(filePath); // do not work in debug mode... why?

        std::shared_ptr<OpenAI::Whisper> whisper = std::dynamic_pointer_cast<OpenAI::Whisper>(_openAiSessions[id]);
        if (whisper == nullptr || !UserHasTokens(id)) return false;

        std::string answer = whisper->Transcript(filePath + ".mp3");

        auto addUsage = AddUsage(id, message->voice->duration * 50);
        DB_TASK(addUsage)

        auto send = _bot->SendMessageAsync(id, answer);
        TELEBOT_TASK(send)

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
    std::cout << command << std::endl;
    int status = system(command.c_str());
    if (status == -1) throw std::runtime_error("ffmpeg process failed!");
}

bool MyBot::MyBot::UserHasTokens(std::int64_t userId)
{
    std::future<int> totalUsageFuture = GetUsage(userId);
    std::future<int> usageLimitFuture = GetUsageLimit(userId);

    int totalUsage = totalUsageFuture.get();
    int usageLimit = usageLimitFuture.get();

    if (totalUsage < usageLimit) return true;

    auto send = _bot->SendMessageAsync(userId, "You do not have tokens.");
    TELEBOT_TASK(send)

    return false;
}