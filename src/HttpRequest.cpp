#include "Telebot/HttpRequest.h"

std::string Telebot::HttpRequest::GenerateHttpRequest()
{
    std::string result;

    if (Body.empty()) result += "GET ";
    else result += "POST ";

    result += Url;
    result += "\r\n";

    result += ProtocolVersion;
    result += ' ';
    result += "Host: ";
    result += Url;

    result += "\r\nConnection: ";
    if (IsKeepAlive) result += "keep-alive";
    else result += "close";

    result += "\r\n";

    if (Body.empty()) result += "\r\n";
    else
    {
        result += "\r\nContent-Type: ";
        result += ContentType;
        result += "\r\nContent-Length: ";
        result += std::to_string(Body.size());

        result += "\r\n\r\n";
        result += Body;
    }

    return result;
}

void Telebot::HttpRequest::ParseHttpRequest(const std::string &requestText)
{

}