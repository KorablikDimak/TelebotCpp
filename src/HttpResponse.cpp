#include "Telebot/HttpResponse.h"

std::string Telebot::HttpResponse::GenerateHttpResponse()
{
    std::string result;

    result += ProtocolVersion;
    result += ' ';
    result += std::to_string(StatusCode);
    result += ' ';
    result += StatusText;

    result += "\r\nConnection: ";
    if (IsKeepAlive) result += "keep-alive";
    else result += "close";

    result += "\r\nContent-Type: ";
    result += ContentType;
    result += "\r\nContent-Length: ";
    result += std::to_string(Body.size());

    result += "\r\n\r\n";
    result += Body;

    return result;
}

void Telebot::HttpResponse::ParseHttpResponse(const std::string &responseText)
{
    
}