#ifndef Telebot_FileH
#define Telebot_FileH

#include <memory>
#include <string>

namespace Telebot
{
    class File
    {
    public:
        typedef std::shared_ptr<File> Ptr;

        std::string FileId;
        std::string FileUniqueId;
        long long FileSize;
        std::string FilePath;
    };
}

#endif