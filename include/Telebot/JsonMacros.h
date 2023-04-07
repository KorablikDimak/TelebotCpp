#ifndef Telebot_JsonMacrosH
#define Telebot_JsonMacrosH

#include <json.hpp>

namespace Telebot
{
    typedef nlohmann::json Json;

    #define VALUE_FROM_JSON(field) \
    object.field = json.value<decltype(object.field)>(#field, decltype(object.field)());

    #define VALUES_FROM_JSON(field) \
    if (json.contains(#field)) \
        for (const Json& element : json.at(#field)) \
        { \
            decltype(object.field)::value_type elementValue = \
                json.value<decltype(object.field)::value_type>(#field, decltype(object.field)::value_type()); \
            object.field.push_back(elementValue); \
        }

    #define OBJECT_FROM_JSON(field) \
    if (json.contains(#field)) *object.field = json.at(#field).get<std::remove_reference<decltype(*object.field)>::type>();

    #define OBJECTS_FROM_JSON(field) \
    if (json.contains(#field)) \
        for (const Json& element : json.at(#field)) \
        { \
            decltype(object.field)::value_type elementPtr = decltype(object.field)::value_type(); \
            *elementPtr = element.get<std::remove_reference<decltype(*elementPtr)>::type>(); \
            object.field.push_back(elementPtr); \
        }
}

#endif