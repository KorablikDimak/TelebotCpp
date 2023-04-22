#include "OpenAI/ChatGpt.h"

const std::string OpenAI::ChatGpt::MODEL = "gpt-3.5-turbo";
const std::int16_t OpenAI::ChatGpt::MAX_TOKENS = 4096;

OpenAI::ChatGpt::ChatGpt(const OpenAIApi::Ptr& api, const std::string& name)
{
    _api = api;
    _name = name;
}
