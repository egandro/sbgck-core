#include "sbgck.hpp"

using namespace SBGCK;

bool Engine::init(string applicationDir, string url, bool isTesting) {
    Log(typelog::INFO) << "Engine init: " << applicationDir;

    if(!fm.init(applicationDir))
        return false;

    if(!sm.init(isTesting))
        return false;

    if(!cm.init(url, isTesting))
        return false;

    return true;
}

bool Engine::loadGame(string gameName) {
    Log(typelog::INFO) << "Engine loadGame: " << gameName;

    if(!fm.openVFS(gameName)) {
        Log(typelog::INFO) << "Engine loadGame - openVFS failed";
        return false;
    }

    return true;
}