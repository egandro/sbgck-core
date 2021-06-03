#include "sbgck.hpp"
#include <soloud/soloud_thread.h>
#include <sbgck_opencv/detector.hpp>
#include <sbgck_opencv/token.hpp>
#include <sbgck_opencv/mathelper.hpp>
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
    for (int i = 0; i < 10; i++)
    {
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

        if (token == NULL)
        {
            Log(typelog::WARN) << "unknown token " << tokenName;
        }
        else
        {
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

bool Engine::init(string applicationDir, string url, bool useDebugCalibrationCache)
{
    Log(typelog::INFO) << "Engine init: " << applicationDir;

    calibrationCache = useDebugCalibrationCache;

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

    if (calibrationCache)
    {
        string cacheDir = fileManager.getCacheDir();
        if (cacheDir.empty())
        {
            Log(typelog::WARN) << "can't use the debug calibration cache";
        }
        else
        {
            string referenceFrameCache = cacheDir + "/frameBoardEmpty.png";
            string homographyReferenceFrameCache = cacheDir + "/homography.homo";
            if (fileManager.physicalFileExist(referenceFrameCache) &&
                fileManager.physicalFileExist(homographyReferenceFrameCache))
            {
                componentManager.currentBoard->frameBoardEmpty = imread(referenceFrameCache, IMREAD_COLOR);
                MatHelper::LoadMatBinary(homographyReferenceFrameCache, componentManager.currentBoard->asset.homography);
                Log(typelog::INFO) << "Engine calibrateReferenceFrame used debug cache from " << referenceFrameCache << " and " << homographyReferenceFrameCache;
                return true;
            }
        }
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

    if (calibrationCache)
    {
        string cacheDir = fileManager.getCacheDir();
        if (cacheDir.empty())
        {
            Log(typelog::WARN) << "can't use the debug calibration cache";
        }
        else
        {
            // save to cache
            string referenceFrameCache = cacheDir + "/frameBoardEmpty.png";
            string homographyReferenceFrameCache = cacheDir + "/homography.homo";
            imwrite(referenceFrameCache, componentManager.currentBoard->frameBoardEmpty);
            MatHelper::SaveMatBinary(homographyReferenceFrameCache, componentManager.currentBoard->asset.homography);
            Log(typelog::INFO) << "Engine calibrateReferenceFrame created debug cache " << referenceFrameCache << " and " << homographyReferenceFrameCache;
        }
    }

    return true;
}

bool Engine::detectColorCalibrationCard()
{
    Log(typelog::INFO) << "Engine calibrateReferenceFrame";
    Log(typelog::WARN) << " detectColorCalibrationCard NOT IMPLEMENTED";
    if (calibrationCache)
    {
        Log(typelog::WARN) << " ... but I could use a cache :)";
    }

    // HACK move to Component manager

    VFSData data;
    string fileName = string("assets/") + "color_checker.png";
    if (!fileManager.readVFSData(fileName, data))
    {
        Log(typelog::ERR) << "Engine detectColorCalibrationCard - color_checker.png loading failed";
        return false;
    }
    Asset reference((const unsigned char *)data.content(), data.size());
    reference.assetDetector = AssetDetector::Feature2D;

    Mat frame;
    if (!cameraManager.getFrame(frame))
    {
        return false;
    }

    Mat result;


    if (!Detector::detectRefereceImage(frame, reference, result, false))
    {
        Log(typelog::ERR) << "color card not detected";
        return false;
    }

    imshow("frame", frame);
    imshow("reference", reference.getDefault().image);
    imshow("result", result);
    waitKey();

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
