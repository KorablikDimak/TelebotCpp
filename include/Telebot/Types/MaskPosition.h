#ifndef Telebot_MaskPositionH
#define Telebot_MaskPositionH

#include <memory>
#include <string>

namespace Telebot
{
    class MaskPosition
    {
    public:
        typedef std::shared_ptr<MaskPosition> Ptr;

        std::string Point;
        float XShift;
        float YShift;
        float Scale;
    };
}

#endif