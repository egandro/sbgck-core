#ifndef _SBGCK_HPP
#define _SBGCK_HPP

#include <string>
#include <vector>
#include <sbgck_opencv/log.hpp>

#include "filemanager.hpp"
#include "soundmanager.hpp"
#include "cameramanager.hpp"
#include "componentmanager.hpp"

namespace SBGCK
{
    class Engine
    {
        FileManager fileManager;
        SoundManager soundManager;
        CameraManager cameraManager;
        ComponentManager componentManager;

    public:
        bool init(string applicationDir, string cameraUrl, bool isTesting=false);
        // TODO: implement this
        //vector<string> loadGameList();
        bool loadGame(string gameName);
    };
}

#endif