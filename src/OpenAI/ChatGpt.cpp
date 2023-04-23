#include "OpenAI/ChatGpt.h"

const std::string OpenAI::ChatGpt::MODEL = "gpt-3.5-turbo";
const unsigned char OpenAI::ChatGpt::N = 1;
const std::int16_t OpenAI::ChatGpt::MAX_TOKENS = 0;

OpenAI::ChatGpt::ChatGpt(const OpenAIApi::Ptr& api, const std::string& name, const std::string& user)
{
    _api = api;
    if (name.size() > 64) throw std::invalid_argument("name is too long");
    _name = name;
    _user = user;

    _role = "user";
    _temperature = 1;
    _top_p = 1;
    _presence_penalty = 0;
    _frequency_penalty = 0;
}

std::string OpenAI::ChatGpt::Chat(const std::string& content)
{
    ChatRequestBody::Ptr chatRequestBody = std::make_shared<ChatRequestBody>();
    chatRequestBody->model = MODEL;

    Message::Ptr message = std::make_shared<Message>();
    message->role = _role;
    message->content = content;
    message->name = _name;

    chatRequestBody->messages.push_back(message);
    chatRequestBody->temperature = _temperature;
    chatRequestBody->top_p = _top_p;
    chatRequestBody->n = N;
    chatRequestBody->stream = false;
    chatRequestBody->max_tokens = MAX_TOKENS;
    chatRequestBody->presence_penalty = _presence_penalty;
    chatRequestBody->frequency_penalty = _frequency_penalty;
    chatRequestBody->user = _user;

    ChatResponseBody::Ptr chatResponseBody = _api->ChatCompletions(chatRequestBody);
    return chatResponseBody->content;
}
