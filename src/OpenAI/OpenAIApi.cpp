#include "OpenAI/OpenAIApi.h"

const std::string OpenAI::OpenAIApi::HOST = "api.openai.com";
const unsigned int OpenAI::OpenAIApi::HTTP_VERSION = 11;

OpenAI::OpenAIApi::OpenAIApi(const std::string& token)
{
    _token = token;
}

Json OpenAI::OpenAIApi::Get(const std::string& methodName)
{
    Common::HttpContext::Ptr httpContext = std::make_shared<Common::HttpContext>();
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
    Common::HttpContext::Ptr httpContext = std::make_shared<Common::HttpContext>();
    httpContext->Request->version(HTTP_VERSION);
    httpContext->Request->method_string("POST");
    httpContext->Request->set(boost::beast::http::field::host, HOST);
    httpContext->Request->target("/v1/" + methodName);
    httpContext->Request->set(boost::beast::http::field::authorization, "Bearer " + _token);

    httpContext->Request->set(boost::beast::http::field::content_type, "application/json");
    httpContext->Request->body() = params.dump();
    httpContext->Request->prepare_payload();

    Common::HttpsClient::SendHttpsAsync(httpContext, true);
    std::string f = httpContext->Response->get().body();
    return Json::parse(httpContext->Response->get().body());
}

OpenAI::ChatResponseBody::Ptr OpenAI::OpenAIApi::ChatCompletions(const ChatRequestBody::Ptr& requestBody)
{
    Json json = requestBody;
    json = Post("chat/completions", json);
    ChatResponseBody::Ptr responseBody = std::make_shared<ChatResponseBody>();
    *responseBody = json.get<ChatResponseBody>();
    return responseBody;
}