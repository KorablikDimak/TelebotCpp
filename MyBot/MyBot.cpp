#include "MyBot.h"

const std::string MyBot::MyBot::LOG_CONFIG_PATH = "LogConfig.xml";
const std::string MyBot::MyBot::OPENAI_USER = "TelegramBot";
const unsigned char MyBot::MyBot::POOL_MAX_SIZE = 3;

MyBot::MyBot::MyBot(const std::string& botToken, const std::string& openAIToken, const std::string& dbConnectionString)
{
    _bot = std::make_unique<Telebot::Telebot>(botToken);
    _openAI = std::make_unique<OpenAI::OpenAI>(openAIToken);
    _dbConnection = std::make_unique<DbProvider::DbConnection>(dbConnectionString, POOL_MAX_SIZE);

    auto factory = CInfoLog::LoggerFactory(LOG_CONFIG_PATH);
    _logger = factory.CreateLogger();

    *_bot->OnCommand("gpt") += THIS_METHOD_HANDLER(&MyBot::GptSession)
    *_bot->OnCommand("usage") += THIS_METHOD_HANDLER(&MyBot::GetUsageInfo)
    *_bot->OnAnyMessage() += THIS_METHOD_HANDLER(&MyBot::Chat)
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

    return _dbConnection->StartTransaction<bool, std::int64_t>(transaction, userId);
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

    return _dbConnection->StartTransaction<bool, std::int64_t>(transaction, userId);
}

std::future<unsigned short> MyBot::MyBot::GetRole(std::int64_t userId)
{
    std::function<unsigned short(pqxx::work&, std::int64_t)> transaction =
            [](pqxx::work& work, const std::int64_t& userId)->unsigned short
            {
                std::string query = "SELECT roleid FROM \"Users\" WHERE userid = " + std::to_string(userId);
                unsigned short result = work.query_value<unsigned short>(query);
                return result;
            };

    return _dbConnection->StartTransaction<unsigned short, std::int64_t>(transaction, userId);
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

    return _dbConnection->StartTransaction<bool, std::int64_t, unsigned short>(transaction, userId, roleId);
}

std::future<unsigned short> MyBot::MyBot::GetContextLimit(std::int64_t userId)
{
    std::function<unsigned short(pqxx::work&, std::int64_t)> transaction =
            [](pqxx::work& work, const std::int64_t& userId)->unsigned short
            {
                std::string query = "SELECT contextlimit FROM \"Users\" WHERE userid = " + std::to_string(userId);
                unsigned short result = work.query_value<unsigned short>(query);
                return result;
            };

    return _dbConnection->StartTransaction<unsigned short, std::int64_t>(transaction, userId);
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

    return _dbConnection->StartTransaction<bool, std::int64_t, unsigned short>(transaction, userId, contextLimit);
}

std::future<int> MyBot::MyBot::GetUsage(std::int64_t userId)
{
    std::function<int(pqxx::work&, std::int64_t)> transaction =
            [](pqxx::work& work, const std::int64_t& userId)->int
            {
                std::string query = "SELECT totalusage FROM \"Users\" WHERE userid = " + std::to_string(userId);
                int result = work.query_value<int>(query);
                return result;
            };

    return _dbConnection->StartTransaction<int, std::int64_t>(transaction, userId);
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

    return _dbConnection->StartTransaction<bool, std::int64_t, int>(transaction, userId, usage);
}

std::future<int> MyBot::MyBot::GetUsageLimit(std::int64_t userId)
{
    std::function<int(pqxx::work&, std::int64_t)> transaction =
            [](pqxx::work& work, const std::int64_t& userId)->int
            {
                std::string query = "SELECT usagelimit FROM \"Users\" WHERE userid = " + std::to_string(userId);
                int result = work.query_value<int>(query);
                return result;
            };

    return _dbConnection->StartTransaction<int, std::int64_t>(transaction, userId);
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

    return _dbConnection->StartTransaction<bool, std::int64_t, int>(transaction, userId, usageLimit);
}

void MyBot::MyBot::Accept()
{
    std::vector<std::pair<std::string, std::string>> commands;
    commands.push_back(std::make_pair("gpt", "start chat gpt session"));
    commands.push_back(std::make_pair("usage", "get information about available tokens"));
    auto setCommandsResult = _bot->SetCommandsAsync(commands);

    _queueController = std::async(std::launch::async, [this](){ ControlQueue(); });
    _queueThreadsChecker = std::async(std::launch::async, [this](){ CheckThreads(_queueThreads, _queueThreadsMutex); });
    _telebotThreadsChecker = std::async(std::launch::async, [this](){ CheckThreads(_telebotThreads, _telebotThreadsMutex); });
    _dbThreadsChecker = std::async(std::launch::async, [this](){ CheckThreads(_dbThreads, _dbThreadsMutex); });

    if (!setCommandsResult.get()) throw std::runtime_error("set command failed");
}

void MyBot::MyBot::Start()
{
    if (_queueControllerTokenSource == nullptr || _queueControllerTokenSource->Token()->IsCancellationRequested())
    {
        _queueControllerTokenSource = std::make_unique<Common::CancellationTokenSource>();
        Accept();
        _bot->Start();
    }
}

void MyBot::MyBot::StartAsync()
{
    if (_queueControllerTokenSource == nullptr || _queueControllerTokenSource->Token()->IsCancellationRequested())
    {
        _queueControllerTokenSource = std::make_unique<Common::CancellationTokenSource>();
        Accept();
        _bot->StartAsync();
    }
}

void MyBot::MyBot::Stop()
{
    if (_queueControllerTokenSource == nullptr || _queueControllerTokenSource->Token()->IsCancellationRequested()) return;
    _queueControllerTokenSource->Cancel();

    std::unique_lock<std::mutex> queueLock(_queueThreadsMutex);
    for (auto& task : _queueThreads) task.get();
    queueLock.unlock();
    _queueThreadsChecker.wait();

    std::unique_lock<std::mutex> telebotLock(_telebotThreadsMutex);
    for (auto& task : _telebotThreads) task.get();
    telebotLock.unlock();
    _telebotThreadsChecker.wait();

    std::unique_lock<std::mutex> dbLock(_dbThreadsMutex);
    for (auto& task : _dbThreads) task.get();
    dbLock.unlock();
    _dbThreadsChecker.wait();

    _queueController.wait();
}

void MyBot::MyBot::GptSession(const Telebot::Message::Ptr& message)
{
    std::int64_t id = message->from->id;

    if (_gptTurboSessions.find(id) == _gptTurboSessions.end())
    {
        OpenAI::GptModel::Ptr chatGpt = _openAI->GptTurboSession(std::to_string(id), OPENAI_USER, OpenAI::Role::User);
        _gptTurboSessions.insert(std::make_pair(id, chatGpt));
        if (!IsUser(id).get()) AddUser(id).get();
    }
    else
    {
        _gptTurboSessions[id] = _openAI->GptTurboSession(std::to_string(id), OPENAI_USER, OpenAI::Role::User);
    }

    auto onSend = _bot->SendMessageAsync(id, "Hello! How can I assist you today?");

    std::unique_lock<std::mutex> telebotLock(_telebotThreadsMutex);
    _telebotThreads.push_back(std::move(onSend));
    telebotLock.unlock();
}

void MyBot::MyBot::GetUsageInfo(const Telebot::Message::Ptr& message)
{
    std::int64_t id = message->from->id;

    std::future<int> totalUsageFuture = GetUsage(id);
    std::future<int> usageLimitFuture = GetUsageLimit(id);

    int totalUsage = totalUsageFuture.get();
    int usageLimit = usageLimitFuture.get();

    auto onSend = _bot->SendMessageAsync(id, "You have " + std::to_string(usageLimit - totalUsage) + " tokens");
    std::unique_lock<std::mutex> telebotLock(_telebotThreadsMutex);
    _telebotThreads.push_back(std::move(onSend));
    telebotLock.unlock();
}

void MyBot::MyBot::Chat(const Telebot::Message::Ptr& message)
{
    std::int64_t id = message->from->id;
    if (_gptTurboSessions.find(id) != _gptTurboSessions.end() && IsUserHasTokens(id))
    {
        std::unique_lock<std::mutex> lock(_queueControllerMutex);
        _requestQueue.push(std::make_pair(_gptTurboSessions[id], message));
        lock.unlock();
    }
}

bool MyBot::MyBot::IsUserHasTokens(std::int64_t userId)
{
    std::future<int> totalUsageFuture = GetUsage(userId);
    std::future<int> usageLimitFuture = GetUsageLimit(userId);

    int totalUsage = totalUsageFuture.get();
    int usageLimit = usageLimitFuture.get();

    if (totalUsage < usageLimit) return true;

    auto onSend = _bot->SendMessageAsync(userId, "You do not have tokens.");
    std::unique_lock<std::mutex> telebotLock(_telebotThreadsMutex);
    _telebotThreads.push_back(std::move(onSend));
    telebotLock.unlock();
    return false;
}

const unsigned short MyBot::MyBot::REQUESTS_PER_MINUTE_LIMIT = 3;

void MyBot::MyBot::ControlQueue()
{
    std::shared_ptr<std::atomic<unsigned short>> requestsPerLastMinute = std::make_shared<std::atomic<unsigned short>>(0);

    while (!_queueControllerTokenSource->Token()->IsCancellationRequested())
    {
        if (*requestsPerLastMinute >= REQUESTS_PER_MINUTE_LIMIT || _requestQueue.empty())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        };

        std::future<bool> queue = std::async(std::launch::async, [this, requestsPerLastMinute]() -> bool
        {
            std::unique_lock<std::mutex> queueLock(_queueControllerMutex);
            if (*requestsPerLastMinute >= REQUESTS_PER_MINUTE_LIMIT || _requestQueue.empty()) return true;
            ++(*requestsPerLastMinute);
            OpenAI::GptModel::Ptr gptModel = _requestQueue.front().first;
            Telebot::Message::Ptr message = _requestQueue.front().second;
            _requestQueue.pop();
            queueLock.unlock();

            std::int64_t id = message->from->id;

            std::string logMessage = "user: " + std::to_string(id) + " to gpt, prompt: " + message->text;
            _logger->Trace(logMessage);

            std::pair<std::string, int> answer = gptModel->Chat(message->text);

            std::unique_lock<std::mutex> bdLock(_dbThreadsMutex);
            std::future<bool> addUsage = AddUsage(id, answer.second);
            _dbThreads.push_back(std::move(addUsage));
            bdLock.unlock();

            std::thread timer([requestsPerLastMinute]()
            {
                std::this_thread::sleep_for(std::chrono::seconds(60));
                if (*requestsPerLastMinute > 0) --(*requestsPerLastMinute);
            });
            timer.detach();

            logMessage = "gpt to user: " + std::to_string(id) + ", answer: " + answer.first;
            _logger->Trace(logMessage);

            auto onSend = _bot->SendMessageAsync(id, answer.first);

            std::unique_lock<std::mutex> telebotLock(_telebotThreadsMutex);
            _telebotThreads.push_back(std::move(onSend));
            telebotLock.unlock();

            return true;
        });

        std::unique_lock<std::mutex> queueLock(_queueThreadsMutex);
        _queueThreads.push_back(std::move(queue));
        queueLock.unlock();
    }
}