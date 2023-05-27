#ifndef OpenAI_OpenAIH
#define OpenAI_OpenAIH

#include "OpenAI/GptTurbo.h"
#include "OpenAI/Whisper.h"
#include "OpenAI/Dalle.h"

namespace OpenAI
{
    class OpenAI
    {
    private:
        OpenAIApi::Ptr _api;

    public:
        explicit OpenAI(const std::string& token);
        ~OpenAI() = default;

        OpenAIModel::Ptr GptTurboSession(const std::string& user = "", const std::string& name = "");
        OpenAIModel::Ptr WhisperSession();
        OpenAIModel::Ptr DalleSession(const std::string& user = "");
    };
}

#endif