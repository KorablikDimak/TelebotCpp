#include "OpenAI/Dalle.h"

const std::string OpenAI::Dalle::MODEL_NAME = "DALLE";

OpenAI::Dalle::Dalle(const OpenAI::OpenAIApi::Ptr& api, const std::string& user)
{
    _api = api;
    _modelName = MODEL_NAME;

    _n = 1;
    _responseFormat = "url";
    _user = user;
}

std::string OpenAI::Dalle::CreateImage(const std::string& prompt, Size size)
{
    CreateImageRequest::Ptr createImageRequest = std::make_shared<CreateImageRequest>();
    createImageRequest->prompt = prompt;
    createImageRequest->n = _n;
    switch (size)
    {
        case Size::Mini:
            createImageRequest->size = "256x256";
            break;
        case Size::Medium:
            createImageRequest->size = "512x512";
            break;
        case Size::Large:
            createImageRequest->size = "1024x1024";
            break;
    }
    createImageRequest->response_format = _responseFormat;
    createImageRequest->user = _user;

    CreateImageResponse::Ptr createImageResponse = _api->CreateImage(createImageRequest);
    return createImageResponse->data[0];
}