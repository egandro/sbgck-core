#ifndef _ENTITIES_HPP
#define _ENTITIES_HPP

#include <sbgck_opencv/log.hpp>
#include "sigslot/property.hpp"

namespace SBGCK
{
    class Sample
    {
    public:
        string fileName;
        //  1.0f is "normal"
        Property<float> volume;
        // -1 is left, 1 is right
        Property<float> pan;
        // true = loop
        Property<bool> loop;

        Sample() : volume(1.0f),
                   pan(0.0f),
                   loop(false)
        {
        }
    };
}

#endif