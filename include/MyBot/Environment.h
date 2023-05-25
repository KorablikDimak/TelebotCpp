#ifndef MyBot_EnvironmentH
#define MyBot_EnvironmentH

#include <map>
#include <mutex>
#include <memory>
#include <vector>
#include <boost/any.hpp>

#include "LanguageCode.h"
#include "pugixml.hpp"

namespace MyBot
{
    class Environment
    {
    private:
        std::map<LanguageCode, std::map<std::string, std::string>> _localisation;
        std::map<std::string, boost::any> _dynamicContainer;
        std::mutex _containerMutex;

    public:
        typedef std::shared_ptr<Environment> Ptr;

        explicit Environment(const std::vector<std::string>& fileNames);
        ~Environment() = default;

        std::string GetLexicalItem(LanguageCode language, const std::string& key);

        bool Contains(const std::string& key);

        template<typename TValue>
        TValue GetValue(const std::string& key)
        {
            std::lock_guard<std::mutex> lock(_containerMutex);
            return boost::any_cast<TValue>(_dynamicContainer.at(key));
        }

        template<typename TValue>
        void SetValue(const std::string& key, const TValue& value)
        {
            if (Contains(key))
            {
                std::lock_guard<std::mutex> lock(_containerMutex);
                _dynamicContainer.at(key) = value;
            }
            else
            {
                std::lock_guard<std::mutex> lock(_containerMutex);
                _dynamicContainer.insert(std::make_pair(key, value));
            }
        }
    };
}

#endif