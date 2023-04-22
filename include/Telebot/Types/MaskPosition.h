#ifndef Telebot_MaskPositionH
#define Telebot_MaskPositionH

#include "Common/JsonMacros.h"

namespace Telebot
{
    class MaskPosition
    {
    public:
        typedef std::shared_ptr<MaskPosition> Ptr;

        std::string point;
        float x_shift;
        float y_shift;
        float scale;
    };

    inline void from_json(const Json& json, MaskPosition& object)
    {
        VALUE_FROM_JSON(point)
        VALUE_FROM_JSON(x_shift)
        VALUE_FROM_JSON(y_shift)
        VALUE_FROM_JSON(scale)
    }
}

#endif