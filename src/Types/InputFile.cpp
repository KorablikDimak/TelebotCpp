#include "Telebot/types/InputFile.h"

#include <fstream>
#include <sstream>
#include <boost/filesystem.hpp>

std::string Read(const std::string& filePath)
{
    std::ifstream in(filePath, std::ios::in | std::ios::binary);
    in.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::ostringstream contents;
    contents << in.rdbuf();
    in.close();
    return contents.str();
}

Telebot::InputFile::Ptr Telebot::InputFile::FromFile(const std::string& filePath, const std::string& mimeType)
{
    InputFile::Ptr file = std::make_shared<InputFile>();

    file->Data = Read(filePath);
    boost::filesystem::path path(filePath);
    file->MimeType = mimeType;
    file->FileName = path.filename().string();

    return file;
}