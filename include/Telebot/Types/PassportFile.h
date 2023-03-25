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
        int FileSize;
        int FileDate;
    };
}

#endif