#ifndef Telebot_HttpResponseH
#define Telebot_HttpResponseH

#include <string>

namespace Telebot
{
    class HttpResponse
    {
    public:
        const std::string ProtocolVersion = "HTTP/1.1";
        unsigned short StatusCode;
        std::string StatusText;
        std::string ContentType;
        std::string Body;
        bool IsKeepAlive;

        HttpResponse() = default;
        ~HttpResponse() = default;

        std::string GenerateHttpResponse();
        void ParseHttpResponse(const std::string& responseText);
    };
}

#endif