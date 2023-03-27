#ifndef Telebot_PassportFileH
#define Telebot_PassportFileH

#include <memory>
#include <string>

namespace Telebot
{
    class PassportFile
    {
    public:
        typedef std::shared_ptr<PassportFile> Ptr;

        std::string FileId;
        std::string FileUniqueId;
        std::int32_t FileSize;
        std::int32_t FileDate;
    };
}

#endif