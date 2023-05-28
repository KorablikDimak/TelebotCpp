#include "OpenAI/OpenAIApi.h"

const std::string OpenAI::OpenAIApi::HOST = "api.openai.com";
const unsigned int OpenAI::OpenAIApi::HTTP_VERSION = 11;

OpenAI::OpenAIApi::OpenAIApi(const std::string& token)
{
    _token = token;
}

Json OpenAI::OpenAIApi::Get(const std::string& methodName)
{
    auto httpContext = std::make_shared<Common::HttpContext<Common::EmptyBody, Common::StringBody>>();
    httpContext->Request->version(HTTP_VERSION);
    httpContext->Request->method_string("GET");
    httpContext->Request->set(boost::beast::http::field::host, HOST);
    httpContext->Request->target("/v1/" + methodName);
    httpContext->Request->set(boost::beast::http::field::authorization, "Bearer " + _token);

    Common::HttpsClient::SendHttpsAsync(httpContext, true);
    return Json::parse(httpContext->Response->get().body());
}

Json OpenAI::OpenAIApi::Post(const std::string& methodName, const Json& params)
{
    auto httpContext = std::make_shared<Common::HttpContext<Common::StringBody, Common::StringBody>>();
    httpContext->Request->version(HTTP_VERSION);
    httpContext->Request->method_string("POST");
    httpContext->Request->set(boost::beast::http::field::host, HOST);
    httpContext->Request->target("/v1/" + methodName);
    httpContext->Request->set(boost::beast::http::field::authorization, "Bearer " + _token);

    httpContext->Request->set(boost::beast::http::field::content_type, "application/json");
    httpContext->Request->body() = params.dump();
    httpContext->Request->prepare_payload();

    Common::HttpsClient::SendHttpsAsync(httpContext, true);
    return Json::parse(httpContext->Response->get().body());
}

OpenAI::ChatCompletionsResponse::Ptr OpenAI::OpenAIApi::ChatCompletions(const ChatCompletionsRequest::Ptr& completionsRequest)
{
    Json requestBody = completionsRequest;
    Json responseBody = Post("chat/completions", requestBody);
    ChatCompletionsResponse::Ptr completionsResponse = std::make_shared<ChatCompletionsResponse>();
    *completionsResponse = responseBody.get<ChatCompletionsResponse>();
    return completionsResponse;
}

OpenAI::FileInfo::Ptr OpenAI::OpenAIApi::UploadFile(const std::string& filePath)
{

}

OpenAI::FileInfo::Ptr OpenAI::OpenAIApi::DeleteFile(const std::string& fileId)
{
    auto httpContext = std::make_shared<Common::HttpContext<Common::EmptyBody, Common::StringBody>>();
    httpContext->Request->version(HTTP_VERSION);
    httpContext->Request->method_string("DELETE");
    httpContext->Request->set(boost::beast::http::field::host, HOST);
    httpContext->Request->target("/v1/files/" + fileId);
    httpContext->Request->set(boost::beast::http::field::authorization, "Bearer " + _token);

    Common::HttpsClient::SendHttpsAsync(httpContext, true);
    Json responseBody = Json::parse(httpContext->Response->get().body());

    FileInfo::Ptr fileInfo = std::make_shared<FileInfo>();
    *fileInfo = responseBody.get<FileInfo>();
    return fileInfo;
}

std::string OpenAI::OpenAIApi::CreateTranscription(const TranscriptionsRequest::Ptr& transcriptionsRequest)
{
    std::string command = "curl https://" + HOST + "/v1/audio/transcriptions"
                          " -H \"Authorization: Bearer " + _token + "\""
                          " -H \"Content-Type: multipart/form-data\""
                          " -F file=\"@" + transcriptionsRequest->file + "\""
                          " -F model=\"" + transcriptionsRequest->model + "\""
                          " -F temperature=\"" + std::to_string(transcriptionsRequest->temperature) + "\"";
    if (!transcriptionsRequest->prompt.empty())
        command = command + " -F prompt=\"" + transcriptionsRequest->prompt + "\"";
    if (!transcriptionsRequest->response_format.empty())
        command = command + " -F response_format=\"" + transcriptionsRequest->response_format + "\"";

    boost::process::ipstream stream;
    boost::process::child process(command, boost::process::std_out > stream);
    std::stringstream ss;
    std::string line;
    while (std::getline(stream, line))
        ss << line << std::endl;
    std::string output = ss.str();
    process.wait();

    Json responseBody = Json::parse(output);
    return responseBody.at("text").get<std::string>();
}

OpenAI::CreateImageResponse::Ptr OpenAI::OpenAIApi::CreateImage(const CreateImageRequest::Ptr& createImageRequest)
{
    Json requestBody = createImageRequest;
    Json responseBody = Post("images/generations", requestBody);
    CreateImageResponse::Ptr createImageResponse = std::make_shared<CreateImageResponse>();
    *createImageResponse = responseBody.get<CreateImageResponse>();
    return createImageResponse;
}