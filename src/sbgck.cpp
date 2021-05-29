#include "sbgck.hpp"
#include <soloud/soloud_thread.h>
#include <sbgck_opencv/detector.hpp>
#include "querytoken.hpp"

using namespace SBGCK;

bool Engine::isAudioTesting = false;
bool Engine::isCameraTesting = false;

void Engine::queryTokens(QueryTokenParam &param, QueryTokenResult &result)
{
    Log(typelog::INFO) << "Engine queryTokens (internal)";
}

bool Engine::setTestingCameraFrame(string fileName) {
    if(isCameraTesting) {
        return cameraManager.setTestingCameraFrame(fileName);
    }
    return true;
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

    string fileName = "audio/" + sampleName;

    return soundManager.play(fileManager, fileName);
}

bool Engine::playSampleSync(string sampleName, bool isLocalized)
{
    Log(typelog::INFO) << "Engine playSampleSync: " << sampleName << isLocalized;

    string fileName = "audio/" + sampleName;
    if (isLocalized)
    {
        fileName = "audio/" + language + "/" + sampleName;
    }

    return soundManager.playSync(fileManager, fileName);
}

bool Engine::stopAllAudio()
{
    Log(typelog::INFO) << "Engine stopAllAudio";
    soundManager.stopAll();
    return true;
}

bool Engine::calibrateReferenceFrame()
{
    Log(typelog::INFO) << "Engine calibrateReferenceFrame";

    if (componentManager.currentBoard == NULL)
    {
        Log(typelog::INFO) << "ComponentManager has no currentBoard - use setBoard()";
        return false;
    }

    // empty the frame
    componentManager.currentBoard->frameBoardEmpty = Mat();

    if (componentManager.currentBoard->asset.getDefault().image.empty())
    {
        Log(typelog::INFO) << "ComponentManager default board as no asset";
        return false;
    }

    Mat frame;
    if (!cameraManager.getFrame(frame))
    {
        return false;
    }

    if(!Detector::calibrateReferenceFrame(frame, *(componentManager.currentBoard))) {
        Log(typelog::INFO) << "Detector calibrateReferenceFrame failed";
    }

    // imshow("frameBoardEmpty", componentManager.currentBoard->frameBoardEmpty);
    // waitKey();

    return true;
}

bool Engine::detectColorCalibrationCard()
{
    Log(typelog::INFO) << "Engine calibrateReferenceFrame";
    Log(typelog::WARN) << " detectColorCalibrationCard NOT IMPLEMENTED";
    return true;
}

string Engine::queryTokens(string json)
{
    Log(typelog::INFO) << "Engine queryTokens" << json;

    return "{ \"error\": \"\" }";
}
