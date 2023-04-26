#include "OpenAI/GptTurbo.h"

const std::string OpenAI::GptTurbo::MODEL_NAME = "gpt-3.5-turbo";
const unsigned char OpenAI::GptTurbo::CONTEXT_SIZE = 2;

OpenAI::GptTurbo::GptTurbo(const OpenAIApi::Ptr& api, const std::string& user, const std::string& name, Role role)
{
    _api = api;
    _modelName = MODEL_NAME;

    _user = user;
    if (name.size() > 64) throw std::invalid_argument("name is too long");
    _name = name;

    switch (role)
    {
        case Role::System:
            _role = "system";
            break;
        case Role::User:
            _role = "user";
            break;
        case Role::Assistant:
            _role = "assistant";
            break;
    }

    _temperature = 1;
    _top_p = 1;
    _n = 1;
    _maxTokens = 0; // infinity
    _presence_penalty = 0;
    _frequency_penalty = 0;
}

std::string OpenAI::GptTurbo::Chat(const std::string& content)
{
    Message::Ptr message = std::make_shared<Message>();
    message->role = _role;
    message->name = _name;

    auto it = _context.begin();
    for (unsigned char i = 0; i < CONTEXT_SIZE && i < _context.size(); ++i)
    {
        message->content += *it;
        message->content += "\n";
        std::advance(it, 1);
    }
    message->content += "<|endoftext|>";
    message->content += content;
    _context.push_back(content);
    if (_context.size() > CONTEXT_SIZE) _context.erase(_context.begin());

    ChatCompletionsRequest::Ptr chatRequestBody = std::make_shared<ChatCompletionsRequest>();
    chatRequestBody->model = _modelName;
    chatRequestBody->messages.push_back(message);
    chatRequestBody->temperature = _temperature;
    chatRequestBody->top_p = _top_p;
    chatRequestBody->n = _n;
    chatRequestBody->stream = false;
    chatRequestBody->max_tokens = _maxTokens;
    chatRequestBody->presence_penalty = _presence_penalty;
    chatRequestBody->frequency_penalty = _frequency_penalty;
    chatRequestBody->user = _user;

    ChatCompletionsResponse::Ptr chatResponseBody = _api->ChatCompletions(chatRequestBody);
    return chatResponseBody->content;
}