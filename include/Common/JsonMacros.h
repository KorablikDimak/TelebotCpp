#ifndef Common_JsonMacrosH
#define Common_JsonMacrosH

#include "json.hpp"

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
if (json.contains(#field)) \
{ \
    if (object.field.get() == nullptr) \
        object.field = std::make_shared<std::remove_reference<decltype(*object.field)>::type>(); \
    *object.field = json.at(#field).get<std::remove_reference<decltype(*object.field)>::type>(); \
}

#define OBJECTS_FROM_JSON(field) \
if (json.contains(#field)) \
    for (const Json& element : json.at(#field)) \
    { \
        decltype(object.field)::value_type elementPtr; \
        elementPtr = std::make_shared<std::remove_reference<decltype(*elementPtr)>::type>(); \
        *elementPtr = element.get<std::remove_reference<decltype(*elementPtr)>::type>(); \
        object.field.push_back(elementPtr); \
    }

#define VALUE_TO_JSON(field) \
json[#field] = object->field;

#define OBJECT_TO_JSON(field) \
if (object->field.get() != nullptr) \
    json[#field] = object->field;

#define OBJECTS_TO_JSON(field) \
for (auto element : object->field) \
{ \
    json[#field].push_back(element); \
}

#endif