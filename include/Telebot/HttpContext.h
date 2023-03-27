#ifndef Telebot_HttpContextH
#define Telebot_HttpContextH

#include <memory>
#include <boost/beast/http.hpp>

typedef boost::beast::http::request<boost::beast::http::string_body> HttpRequest;
typedef boost::beast::http::response<boost::beast::http::string_body> HttpResponse;

namespace Telebot
{
    class HttpContext
    {
    public:
        HttpContext();
        ~HttpContext() = default;

        std::unique_ptr<HttpRequest> Request;
        std::unique_ptr<HttpResponse> Response;
    };
}

#endif