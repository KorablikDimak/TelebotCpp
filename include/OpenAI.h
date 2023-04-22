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
    };
}

#endif