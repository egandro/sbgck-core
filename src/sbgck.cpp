#include "sbgck.hpp"
#include <soloud/soloud_thread.h>
#include <sbgck_opencv/detector.hpp>
#include <sbgck_opencv/token.hpp>
#include "querytoken.hpp"

using namespace SBGCK;
using namespace nlohmann;

bool Engine::isAudioTesting = false;
bool Engine::isCameraTesting = false;

void Engine::queryTokens(QueryTokenParam &param, QueryTokenResult &result)
{
    Log(typelog::INFO) << "Engine queryTokens (internal)";

    if (componentManager.currentBoard == NULL)
    {
        Log(typelog::INFO) << "ComponentManager has no currentBoard - use setBoard()";
        result.error = "no currentBoard set - use setBoard()";
        return;
    }

    Mat frame;

    // TODO: fix me?
    for(int i = 0; i< 10; i++) {
        if (!cameraManager.getFrame(frame))
        {
            result.error = "can't get camera frame";
            return;
        }
    }

    DetectorTokenConfig cfg;

    cfg.frame = &frame;
    cfg.board = componentManager.currentBoard;
    cfg.showColorDiff = param.showColorDiff;
    cfg.showAllROIs = param.showAllROIs;
    cfg.showContours = param.showContours;

    for (size_t i = 0; i < param.names.size(); i++)
    {
        std::string tokenName = param.names[i];

        Token *token = componentManager.getToken(tokenName);

        if(token == NULL) {
            Log(typelog::WARN) << "unknown token " << tokenName;
        } else {
            cfg.tokens.push_back(token);
        }
    }

    for (size_t i = 0; i < param.ROI.size(); i++)
    {
        cfg.ROIs.push_back(param.ROI[i]);
    }

    if (!Detector::queryTokens(cfg))
    {
        Log(typelog::INFO) << "Detector queryTokens failed";
        result.error = "can't query tokens";
        return;
    }

    for (size_t i = 0; i < cfg.result.size(); i++)
    {
        QueryTokenResultToken item;

        item.ROI = cfg.result[i].first;
        item.name = cfg.result[i].second;

        result.tokens.push_back(item);
    }
}

bool Engine::setTestingCameraFrame(string fileName)
{
    if (isCameraTesting)
    {
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

    if (!Detector::calibrateReferenceFrame(frame, *(componentManager.currentBoard)))
    {
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

string Engine::queryTokens(string jsonStr)
{
    Log(typelog::INFO) << "Engine queryTokens" << jsonStr;

    QueryTokenResult result;

    try
    {
        json json = json.parse(jsonStr);
        QueryTokenParam queryTokenParam = json.get<QueryTokenParam>();
        queryTokens(queryTokenParam, result);
    }
    catch (json::exception &error)
    {
        Log(typelog::ERR) << "Engine queryTokens - json::exception " << error.what();
        result.error = "json parse error";
    }

    json j_result = result;
    string resultStr = j_result.dump();
    return resultStr;
}
