#ifndef OpenAI_DalleH
#define OpenAI_DalleH

#include "OpenAIModel.h"
#include "Types/Size.h"

namespace OpenAI
{
    class Dalle : public OpenAIModel
    {
    private:
        static const std::string MODEL_NAME;
        static const std::string RESPONSE_FORMAT;
        static const unsigned char N;

        std::string _user;
        Size _size;

    public:
        typedef std::shared_ptr<Dalle> Ptr;

        explicit Dalle(const OpenAIApi::Ptr& api, const std::string& user = "");
        ~Dalle() override = default;

        std::string CreateImage(const std::string& prompt);

        void SetSize(Size size);
    };
}

#endif