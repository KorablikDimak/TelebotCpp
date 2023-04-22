#ifndef OpenAI_OpenAIApiH
#define OpenAI_OpenAIApiH

#include "Common/HttpsClient.h"
#include "Types/ChatRequestBody.h"
#include "Types/ChatResponseBody.h"

namespace OpenAI
{
    class OpenAIApi
    {
    private:
        static const std::string HOST;
        static const unsigned int HTTP_VERSION;

        std::string _token;

        Json Get(const std::string& methodName);
        Json Post(const std::string& methodName, const Json& params);

    public:
        typedef std::shared_ptr<OpenAIApi> Ptr;

        explicit OpenAIApi(const std::string& token);
        ~OpenAIApi() = default;

        ChatResponseBody::Ptr ChatCompletions(const ChatRequestBody::Ptr& requestBody);
    };
}

#endif