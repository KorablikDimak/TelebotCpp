#ifndef Common_HttpContextH
#define Common_HttpContextH

#include <memory>
#include <boost/beast/http.hpp>

typedef boost::beast::http::request<boost::beast::http::string_body> HttpRequest;
typedef boost::beast::http::response_parser<boost::beast::http::string_body> HttpResponse;

namespace Common
{
    class HttpContext
    {
    public:
        typedef std::shared_ptr<HttpContext> Ptr;

        HttpContext();
        ~HttpContext() = default;

        std::unique_ptr<HttpRequest> Request;
        std::unique_ptr<HttpResponse> Response;
    };
}

#endif