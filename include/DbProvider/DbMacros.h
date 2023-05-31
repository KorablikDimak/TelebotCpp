#ifndef DbProvider_DbMacrosH
#define DbProvider_DbMacrosH

#include <pqxx/pqxx>

#define GET_VALUE(field) \
object->field = row[#field].as<decltype(object->field)>()

#define GET_ENUM(field) \
FromString(object->field, row[#field].as<std::string>())

#endif