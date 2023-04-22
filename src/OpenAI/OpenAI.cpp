#include "OpenAI.h"

OpenAI::OpenAI::OpenAI(const std::string &token)
{
    _api = std::make_shared<OpenAIApi>(token);
}
