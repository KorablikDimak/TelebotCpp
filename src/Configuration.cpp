#include "Telebot/Configuration.h"

ConfigDictionary* Telebot::Configuration::GetConfig()
{
    return _config.get();
}