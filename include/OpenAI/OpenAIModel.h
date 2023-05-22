#ifndef OpenAI_OpenAIModelH
#define OpenAI_OpenAIModelH

#include "OpenAIApi.h"

namespace OpenAI
{
    class OpenAIModel
    {
    protected:
        OpenAIApi::Ptr _api;
        std::string _modelName;

    public:
        typedef std::shared_ptr<OpenAIModel> Ptr;

        OpenAIModel() = default;
        virtual ~OpenAIModel() = default;
        std::string GetModelName();
    };
}

#endif