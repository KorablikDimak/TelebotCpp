#include "OpenAI.h"

OpenAI::OpenAI::OpenAI(const std::string &token)
{
    _api = std::make_shared<OpenAIApi>(token);
}

OpenAI::OpenAIModel::Ptr OpenAI::OpenAI::GptTurboSession(const std::string& user, const std::string& name, Role role)
{
    return OpenAIModel::Ptr(new GptTurbo(_api, user, name, role));
}

OpenAI::OpenAIModel::Ptr OpenAI::OpenAI::WhisperSession()
{
    return OpenAIModel::Ptr(new Whisper(_api));
}

OpenAI::OpenAIModel::Ptr OpenAI::OpenAI::DalleSession(const std::string& user)
{
    return OpenAIModel::Ptr(new Dalle(_api, user));
}