#include "sbgck.hpp"
#include <soloud/soloud_thread.h>

using namespace SBGCK;

void Engine::queryTokens(QueryTokenParam &param, QueryTokenResult &result)
{
    Log(typelog::INFO) << "Engine queryTokens (internal)";
}

bool Engine::init(string applicationDir, string url)
{
    Log(typelog::INFO) << "Engine init: " << applicationDir;

    if (!fileManager.init(applicationDir))
        return false;

    if (!soundManager.init(isAudioTesting))
        return false;

    if (!cameraManager.init(url, isCameraTesting))
        return false;

    return true;
}

bool Engine::loadGame(string gameName, string lang)
{
    Log(typelog::INFO) << "Engine loadGame: " << gameName << "lang: " << lang;
    language = lang;

    if (!fileManager.openVFS(gameName))
    {
        Log(typelog::INFO) << "Engine loadGame - fileManager.openVFS failed";
        return false;
    }

    string fileName = "gameconfig.json";
    if (!componentManager.loadFromComponentFile(fileManager, fileName))
    {
        Log(typelog::INFO) << "Engine loadGame - componentManager.loadFromComponentFile - " << fileName << " - failed";
        return false;
    }

    return true;
}

bool Engine::setBoard(string boardName)
{
    Log(typelog::INFO) << "Engine setBoard: " << boardName;

    if (!componentManager.setBoard(boardName, false))
    {
        Log(typelog::INFO) << "Engine setBoard - componentManager.setBoard - " << boardName << " - failed";
        return false;
    }

    return true;
}

bool Engine::playSample(string sampleName)
{
    Log(typelog::INFO) << "Engine playSample: " << sampleName;

    Sample desc;
    desc.fileName = "audio/" + sampleName;

    SampleVFS sample(&soundManager);
    if (!sample.load(fileManager, desc))
    {
        Log(typelog::ERR) << "SampleVFS load failed " << sampleName;
        return false;
    }

    return sample.play();
}

bool Engine::playSampleSync(string sampleName, bool isLocalized)
{
    Log(typelog::INFO) << "Engine playSampleSync: " << sampleName << isLocalized;

    Sample desc;
    desc.fileName = "audio/" + sampleName;
    if(isLocalized) {
        desc.fileName = "audio/" + language + "/" + sampleName;
    }
    desc.loop = false; // MUST be false

    SampleVFS sample(&soundManager);
    if (!sample.load(fileManager, desc))
    {
        Log(typelog::ERR) << "SampleVFS load failed " << sampleName;
        return false;
    }

    if (!sample.play())
    {
        return false;
    }

    while (soundManager.soloud.isValidVoiceHandle(sample.getHandle()))
    {
        // wait consume some time
        SoLoud::Thread::sleep(100);
        // MUST be false - we do an active CPU hold here (may be bad...)
        desc.loop = false;
    }

    return true;
}

bool Engine::stopAllAudio()
{
    Log(typelog::INFO) << "Engine stopAllAudio";
    return false;
}

bool Engine::calibrateReferenceFrame()
{
    Log(typelog::INFO) << "Engine calibrateReferenceFrame";
    return false;
}

bool Engine::detectColorCalibrationCard()
{
    Log(typelog::INFO) << "Engine calibrateReferenceFrame";
    return false;
}

string Engine::queryTokens(string json)
{
    Log(typelog::INFO) << "Engine queryTokens" << json;

    return "{ \"error\": \"\" }";
}
