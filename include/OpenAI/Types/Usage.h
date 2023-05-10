#ifndef OpenAI_UsageH
#define OpenAI_UsageH

#include "Common/JsonMacros.h"

namespace OpenAI
{
    class Usage
    {
    public:
        typedef std::shared_ptr<Usage> Ptr;

        std::int32_t prompt_tokens;
        std::int32_t completion_tokens;
        std::int32_t total_tokens;
    };

    inline void from_json(const Json& json, Usage& object)
    {
        VALUE_FROM_JSON(prompt_tokens)
        VALUE_FROM_JSON(completion_tokens)
        VALUE_FROM_JSON(total_tokens)
    }
}

#endif