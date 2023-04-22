#ifndef OpenAI_ChatRequestBodyH
#define OpenAI_ChatRequestBodyH

#include <map>

#include "Common/JsonMacros.h"

namespace OpenAI
{
    class ChatRequestBody
    {
    public:
        typedef std::shared_ptr<ChatRequestBody> Ptr;

        std::string model;
        std::string role;
        std::string content;
        std::string name;
        float temperature;
        float top_p;
        int n;
        bool stream;
        std::string stop;
        int max_tokens;
        float presence_penalty;
        float frequency_penalty;
        std::map<std::string, signed char> logit_bias; // do not use!
        std::string user;
    };

    inline void to_json(Json& json, const ChatRequestBody& object)
    {
        VALUE_TO_JSON(model)
        json["messages"] = { {"role", object.role}, {"content", object.content}, {"name", object.name} };
        VALUE_TO_JSON(temperature)
        VALUE_TO_JSON(top_p)
        VALUE_TO_JSON(n)
        VALUE_TO_JSON(stream)
        VALUE_TO_JSON(stop)
        VALUE_TO_JSON(max_tokens)
        VALUE_TO_JSON(presence_penalty)
        VALUE_TO_JSON(frequency_penalty)
        // logit_bias
        VALUE_TO_JSON(user)
    }
}

#endif