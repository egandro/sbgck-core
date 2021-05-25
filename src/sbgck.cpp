#include "sbgck.hpp"

using namespace SBGCK;

bool Engine::init(string applicationDir, string url) {
    Log(typelog::INFO) << "Engine init: " << applicationDir;

    if(!fileManager.init(applicationDir))
        return false;

    if(!soundManager.init(isTesting))
        return false;

    if(!cameraManager.init(url, isTesting))
        return false;

    return true;
}

bool Engine::loadGame(string gameName, string lang) {
    Log(typelog::INFO) << "Engine loadGame: " << gameName << "lang: " << lang;
    language = lang;

    if(!fileManager.openVFS(gameName)) {
        Log(typelog::INFO) << "Engine loadGame - openVFS failed";
        return false;
    }

    return true;
}

void Engine::queryTokens(QueryTokenParam &param, QueryTokenResult &result) {
    Log(typelog::INFO) << "Engine queryTokens (internal)";
}


bool Engine::playSample(string sampleName) {
    Log(typelog::INFO) << "Engine playSample: " << sampleName;
    return false;
}


bool Engine::playSampleSync(string sampleName, bool isLocalized) {
    Log(typelog::INFO) << "Engine playSampleSync: " << sampleName << isLocalized;
    return false;
}

void Engine::stopAllAudio() {
    Log(typelog::INFO) << "Engine stopAllAudio";
}

bool Engine::calibrateReferenceFrame() {
    Log(typelog::INFO) << "Engine calibrateReferenceFrame";
    return false;
}

bool Engine::detectColorCalibrationCard() {
    Log(typelog::INFO) << "Engine calibrateReferenceFrame";
    return false;
}

string Engine::queryTokens(string json) {
    Log(typelog::INFO) << "Engine queryTokens" << json;

    return "{ \"error\": \"\" }";
}

