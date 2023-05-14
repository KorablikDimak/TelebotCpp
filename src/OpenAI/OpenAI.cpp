#include "OpenAI.h"

OpenAI::OpenAI::OpenAI(const std::string &token)
{
    _api = std::make_shared<OpenAIApi>(token);
}

OpenAI::OpenAiModel::Ptr OpenAI::OpenAI::GptTurboSession(const std::string& user, const std::string& name, Role role)
{
    return OpenAiModel::Ptr(new GptTurbo(_api, user, name, role));
}

OpenAI::OpenAiModel::Ptr OpenAI::OpenAI::WhisperSession()
{
    return OpenAiModel::Ptr(new Whisper(_api));
}