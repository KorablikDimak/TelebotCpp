#ifndef Telebot_InputFileH
#define Telebot_InputFileH

#include <memory>
#include <string>

namespace Telebot
{
    class InputFile
    {
    public:
        typedef std::shared_ptr<InputFile> Ptr;

        std::string Data;
        std::string MimeType;
        std::string FileName;

        static InputFile::Ptr FromFile(const std::string& filePath, const std::string& mimeType);
    };
}

#endif