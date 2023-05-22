#ifndef OpenAI_WhisperH
#define OpenAI_WhisperH

#include "OpenAIModel.h"

namespace OpenAI
{
    class Whisper : public OpenAIModel
    {
    private:
        static const std::string MODEL_NAME;

        float _temperature;

    public:
        typedef std::shared_ptr<Whisper> Ptr;

        explicit Whisper(const OpenAIApi::Ptr& api);
        ~Whisper() override = default;

        std::string Transcript(const std::string& filePath);
    };
}

#endif