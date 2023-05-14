#include "OpenAI/Whisper.h"

const std::string OpenAI::Whisper::MODEL_NAME = "whisper-1";

OpenAI::Whisper::Whisper(const OpenAIApi::Ptr& api)
{
    _api = api;
    _modelName = MODEL_NAME;
    _temperature = 0;
}

std::string OpenAI::Whisper::Transcript(const std::string& filePath)
{
    TranscriptionsRequest::Ptr transcriptionsRequest = std::make_shared<TranscriptionsRequest>();
    transcriptionsRequest->file = filePath;
    transcriptionsRequest->model = _modelName;
    transcriptionsRequest->temperature = _temperature;
    return _api->CreateTranscription(transcriptionsRequest);
}