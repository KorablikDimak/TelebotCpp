#ifndef MyBot_RoleH
#define MyBot_RoleH

#include <string>

namespace MyBot
{
    enum class Role
    {
        System = 0,
        Admin = 1,
        User = 2
    };

    inline void FromString(Role& role, const std::string& roleString)
    {
        if (roleString == "system")
            role = Role::System;
        else if (roleString == "admin")
            role = Role::Admin;
        else if (roleString == "user")
            role = Role::User;
    }

    inline std::string ToString(Role role)
    {
        switch (role)
        {
            case Role::System:
                return "system";
            case Role::Admin:
                return "admin";
            case Role::User:
                return "user";
        }
    }
}

#endif