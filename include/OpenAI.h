#ifndef OpenAI_OpenAIH
#define OpenAI_OpenAIH

#include "OpenAI/GptTurbo.h"
#include "OpenAI/Whisper.h"

namespace OpenAI
{
    class OpenAI
    {
    private:
        OpenAIApi::Ptr _api;

    public:
        explicit OpenAI(const std::string& token);
        ~OpenAI() = default;

        OpenAIModel::Ptr GptTurboSession(const std::string& user = "", const std::string& name = "", Role role = Role::User);
        OpenAIModel::Ptr WhisperSession();
    };
}

#endif