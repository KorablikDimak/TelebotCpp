#ifndef OpenAI_ChatGptH
#define OpenAI_ChatGptH

#include "OpenAIApi.h"

namespace OpenAI
{
    class OpenAiModel
    {
    protected:
        OpenAIApi::Ptr _api;
        std::string _modelName;

    public:
        typedef std::shared_ptr<OpenAiModel> Ptr;

        OpenAiModel() = default;
        virtual ~OpenAiModel() = default;
        std::string GetModelName();
    };
}

#endif