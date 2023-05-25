#ifndef MyBot_LanguageCodeH
#define MyBot_LanguageCodeH

#include <string>

namespace MyBot
{
    enum class LanguageCode
    {
        English = 0,
        Russian = 1
    };

    inline LanguageCode FromInt(std::size_t languageCode)
    {
        switch (languageCode)
        {
            case 0:
                return LanguageCode::English;
            case 1:
                return LanguageCode::Russian;
        }
    }

    inline std::string ToString(LanguageCode languageCode)
    {
        switch (languageCode)
        {
            case LanguageCode::English:
                return "0";
            case LanguageCode::Russian:
                return "1";
        }
    }
}

#endif