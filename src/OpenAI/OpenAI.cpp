#include "OpenAI.h"

OpenAI::OpenAI::OpenAI(const std::string &token)
{
    _api = std::make_shared<OpenAIApi>(token);
}

OpenAI::ChatGpt::Ptr OpenAI::OpenAI::StartChatGptSession(const std::string& name, const std::string& user)
{
    return std::make_shared<ChatGpt>(_api, name, user);
}
