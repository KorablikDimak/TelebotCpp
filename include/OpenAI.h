#ifndef OpenAI_OpenAIH
#define OpenAI_OpenAIH

#include "OpenAI/GptTurbo.h"

namespace OpenAI
{
    class OpenAI
    {
    private:
        OpenAIApi::Ptr _api;

    public:
        explicit OpenAI(const std::string& token);
        ~OpenAI() = default;

        GptModel::Ptr GptTurboSession(const std::string& user = "", const std::string& name = "", Role role = Role::User);
    };
}

#endif