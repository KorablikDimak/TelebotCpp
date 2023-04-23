#ifndef OpenAI_OpenAIH
#define OpenAI_OpenAIH

#include "OpenAI/ChatGpt.h"

namespace OpenAI
{
    class OpenAI
    {
    private:
        OpenAIApi::Ptr _api;

    public:
        explicit OpenAI(const std::string& token);
        ~OpenAI() = default;

        ChatGpt::Ptr StartChatGptSession(const std::string& name, const std::string& user = "");
    };
}

#endif