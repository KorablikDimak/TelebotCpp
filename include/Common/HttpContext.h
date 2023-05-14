#ifndef Common_HttpContextH
#define Common_HttpContextH

#include <memory>
#include <boost/beast/http.hpp>

typedef boost::beast::http::empty_body EmptyBody;
typedef boost::beast::http::string_body StringBody;
typedef boost::beast::http::file_body FileBody;
typedef boost::beast::http::buffer_body BufferBody;

namespace Common
{
    template <typename RequestBody, typename ResponseBody>
    class HttpContext
    {
    public:
        typedef boost::beast::http::request<RequestBody> HttpRequest;
        typedef boost::beast::http::response_parser<ResponseBody> HttpResponse;

        std::unique_ptr<HttpRequest> Request;
        std::unique_ptr<HttpResponse> Response;

        HttpContext()
        {
            Request = std::make_unique<HttpRequest>();
            Response = std::make_unique<HttpResponse>();
        }
        ~HttpContext() = default;
    };
}

#endif