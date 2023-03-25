#ifndef Telebot_HttpRequestH
#define Telebot_HttpRequestH

#include <string>
#include <boost/asio.hpp>

namespace Telebot
{
    class HttpRequest
    {
    public:
        const std::string ProtocolVersion = "HTTP/1.1";
        std::string Url;
        std::string ContentType;
        std::string Body;
        bool IsKeepAlive;

        HttpRequest() = default;
        ~HttpRequest() = default;

        std::string GenerateHttpRequest();
        void ParseHttpRequest(const std::string& requestText);
    };
}

#endif