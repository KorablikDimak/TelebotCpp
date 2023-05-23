#ifndef OpenAI_DalleH
#define OpenAI_DalleH

#include "OpenAIModel.h"

namespace OpenAI
{
    enum class Size
    {
        Mini, Medium, Large
    };

    class Dalle : public OpenAIModel
    {
    private:
        static const std::string MODEL_NAME;

        unsigned char _n;
        std::string _responseFormat;
        std::string _user;

    public:
        typedef std::shared_ptr<Dalle> Ptr;

        explicit Dalle(const OpenAIApi::Ptr& api, const std::string& user = "");
        ~Dalle() override = default;

        std::string CreateImage(const std::string& prompt, Size size = Size::Large);
    };
}

#endif