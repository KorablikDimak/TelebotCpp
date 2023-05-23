#ifndef OpenAI_CreateImageResponseH
#define OpenAI_CreateImageResponseH

#include "Common/JsonMacros.h"

namespace OpenAI
{
    class CreateImageResponse
    {
    public:
        typedef std::shared_ptr<CreateImageResponse> Ptr;

        std::int64_t created;
        std::vector<std::string> data;
    };

    inline void from_json(const Json& json, CreateImageResponse& object)
    {
        VALUE_FROM_JSON(created)

        if (json.contains("data"))
            for (const Json& url : json.at("data"))
                if (url.contains("url"))
                    object.data.push_back(url.at("url").get<std::string>());
    }
}

#endif