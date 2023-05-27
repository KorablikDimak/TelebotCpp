#ifndef MyBot_LanguageCodeH
#define MyBot_LanguageCodeH

#include <string>

namespace MyBot
{
    enum class Language
    {
        English = 0,
        Russian = 1
    };

    inline void FromString(Language& language, const std::string& languageString)
    {
        if (languageString == "English")
            language = Language::English;
        else if (languageString == "Russian")
            language = Language::Russian;
    }

    inline std::string ToString(Language language)
    {
        switch (language)
        {
            case Language::English:
                return "English";
            case Language::Russian:
                return "Russian";
        }
    }
}

#endif