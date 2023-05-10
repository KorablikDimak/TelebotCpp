#ifndef OpenAI_ChatGptH
#define OpenAI_ChatGptH

#include "OpenAIApi.h"

namespace OpenAI
{
    class GptModel
    {
    protected:
        OpenAIApi::Ptr _api;
        std::string _modelName;

    public:
        typedef std::shared_ptr<GptModel> Ptr;

        GptModel() = default;
        virtual ~GptModel() = default;

        virtual std::pair<std::string, int> Chat(const std::string& content) = 0;
        std::string GetModelName();
    };
}

#endif