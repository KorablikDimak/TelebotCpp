#ifndef Telebot_UserProfilePhotosH
#define Telebot_UserProfilePhotosH

#include "PhotoSize.h"

#include <vector>

namespace Telebot
{
    class UserProfilePhotos
    {
    public:
        typedef std::shared_ptr<UserProfilePhotos> Ptr;

        std::int32_t TotalCount;
        std::vector<std::vector<PhotoSize::Ptr>> Photos;
    };
}

#endif