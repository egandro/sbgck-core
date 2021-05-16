#ifndef _SBGCK_HPP
#define _SBGCK_HPP

#include <string>
#include <sbgck_opencv/log.hpp>

#include "filemanager.hpp"

using namespace std;

namespace SBGCK
{
    class Engine
    {
    public:
        static Filemanager fm;

        static string getVersion();

        static bool init(string applicationDir, string cfg);
    };
}

#endif