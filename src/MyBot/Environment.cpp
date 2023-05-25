#include "MyBot/Environment.h"

MyBot::Environment::Environment(const std::vector<std::string>& fileNames)
{
    for (const std::string& fileName : fileNames)
    {
        pugi::xml_document document;
        pugi::xml_parse_result result = document.load_file(fileName.c_str());

        for (const pugi::xml_node& language : document.child("localisation").children())
        {
            std::string languageName = language.name();

            if (languageName == "english")
            {
                if (_localisation.find(LanguageCode::English) == _localisation.end())
                    _localisation.insert(std::make_pair(LanguageCode::English, std::map<std::string, std::string>()));

                for (const pugi::xml_node& lexicalItem : language.children())
                    _localisation.at(LanguageCode::English).insert(std::make_pair(lexicalItem.name(), lexicalItem.child_value()));
            }
            else if (languageName == "russian")
            {
                if (_localisation.find(LanguageCode::Russian) == _localisation.end())
                    _localisation.insert(std::make_pair(LanguageCode::Russian, std::map<std::string, std::string>()));

                for (const pugi::xml_node& lexicalItem : language.children())
                    _localisation.at(LanguageCode::Russian).insert(std::make_pair(lexicalItem.name(), lexicalItem.child_value()));
            }
        }
    }
}

std::string MyBot::Environment::GetLexicalItem(MyBot::LanguageCode language, const std::string& key)
{
    auto languageIterator = _localisation.find(language);
    if (languageIterator == _localisation.end()) return "";

    auto iterator = _localisation.at(language).find(key);
    if (iterator == _localisation.at(language).end()) return "";
    else return _localisation.at(language).at(key);
}

bool MyBot::Environment::Contains(const std::string& key)
{
    std::lock_guard<std::mutex> lock(_containerMutex);
    return _dynamicContainer.find(key) != _dynamicContainer.end();
}