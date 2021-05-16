#include "sbgck.hpp"

using namespace SBGCK;

bool Engine::init(string applicationDir, string url, bool isTesting) {
    Log(typelog::INFO) << "Engine init: " << applicationDir;

    if(!fileManager.init(applicationDir))
        return false;

    if(!soundManager.init(isTesting))
        return false;

    if(!cameraManager.init(url, isTesting))
        return false;

    return true;
}

bool Engine::loadGame(string gameName) {
    Log(typelog::INFO) << "Engine loadGame: " << gameName;

    if(!fileManager.openVFS(gameName)) {
        Log(typelog::INFO) << "Engine loadGame - openVFS failed";
        return false;
    }

    return true;
}