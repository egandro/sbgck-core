#ifndef _SBGCK_HPP
#define _SBGCK_HPP

#include <string>
#include <sbgck_opencv/log.hpp>

#include "filemanager.hpp"

using namespace std;

namespace SBGCK
{
    class Sample
    {
    public:
        string fileName;
        //  1.0f is "normal"
        float volume;
        // -1 is left, 1 is right
        float pan;
        // true = loop
        bool loop;

        Sample() : volume(1.0f),
                   pan(0.0f),
                   loop(false)
        {
        }
    };

    class Engine
    {
    public:
        static Filemanager fm;

        static string getVersion();

        static bool init(string applicationDir, string cfg);
    };
}

#endif