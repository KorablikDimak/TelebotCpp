#ifndef Telebot_ConfigurationH
#define Telebot_ConfigurationH

#include <map>
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>
#include <boost/algorithm/string.hpp>

#include "pugixml.hpp"

typedef std::map<std::string, std::string> ConfigDictionary;

namespace Telebot
{
    class Configuration
    {
    private:
        std::unique_ptr<ConfigDictionary> _config;

    public:
        template<typename T>
        explicit Configuration(const T& fileName)
        {
            _config = std::make_unique<ConfigDictionary>();

            std::stringstream stream;
            stream << fileName;
            std::string fileNameString = stream.str();

            pugi::xml_document document;
            pugi::xml_parse_result result = document.load_file(fileNameString.c_str());

            if (result)
            {
                for (pugi::xml_attribute attribute: document.child("client").attributes())
                {
                    std::string attributeName = attribute.name();
                    boost::algorithm::to_lower(attributeName);
                    _config->insert(std::make_pair(attributeName, attribute.value()));
                }
            }
            else
            {
                std::cout << fileNameString.c_str() <<  " parse FAILED!\n";
                std::cout << "Error description: " << result.description() << std::endl;
            }
        }

        ~Configuration() = default;

        ConfigDictionary* GetConfig();
    };
}

#endif