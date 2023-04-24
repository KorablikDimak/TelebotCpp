#include "OpenAI.h"

OpenAI::OpenAI::OpenAI(const std::string &token)
{
    _api = std::make_shared<OpenAIApi>(token);
}

OpenAI::GptModel::Ptr OpenAI::OpenAI::GptTurboSession(const std::string& user, const std::string& name, Role role)
{
    return GptModel::Ptr(new GptTurbo(_api, user, name, role));
}
