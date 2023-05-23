#ifndef OpenAI_OpenAIApiH
#define OpenAI_OpenAIApiH

#include <boost/process.hpp>

#include "Common/HttpsClient.h"
#include "Types/ChatCompletionsRequest.h"
#include "Types/ChatCompletionsResponse.h"
#include "Types/TranscriptionsRequest.h"
#include "Types/FileInfo.h"
#include "Types/CreateImageRequest.h"
#include "Types/CreateImageResponse.h"

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

        ChatCompletionsResponse::Ptr ChatCompletions(const ChatCompletionsRequest::Ptr& completionsRequest);
        FileInfo::Ptr UploadFile(const std::string& filePath);
        FileInfo::Ptr DeleteFile(const std::string& fileId);
        std::string CreateTranscription(const TranscriptionsRequest::Ptr& transcriptionsRequest);
        CreateImageResponse::Ptr CreateImage(const CreateImageRequest::Ptr& createImageRequest);
    };
}

#endif