#ifndef _SBGCK_HPP
#define _SBGCK_HPP

#include <string>
#include <vector>
#include <sbgck_opencv/log.hpp>

#include "internal/filemanager.hpp"
#include "internal/soundmanager.hpp"
#include "internal/cameramanager.hpp"
#include "internal/componentmanager.hpp"

namespace SBGCK
{
    class QueryTokenParam;
    class QueryTokenResult;

    class Engine
    {
        string language;
        bool calibrationCache;

        FileManager fileManager;
        SoundManager soundManager;
        CameraManager cameraManager;
        ComponentManager componentManager;
        void queryTokens(QueryTokenParam &param, QueryTokenResult &result);

    public:
        static bool isAudioTesting;
        static bool isCameraTesting;

        Engine()
            : calibrationCache(false) {
        }


        bool setTestingCameraFrame(string fileName);

        //////////////////////////////////////////
        // Management API for UI
        //////////////////////////////////////////

        bool init(string applicationDir, string cameraUrl, bool useDebugCalibrationCache=false);
        bool loadGame(string gameName, string lang);

        //////////////////////////////////////////
        // Core Engine API
        //////////////////////////////////////////

        bool setBoard(string boardName);
        bool playSample(string sampleName);
        bool playSampleSync(string sampleName, bool isLocalized);
        bool stopAllAudio();
        bool calibrateReferenceFrame();
        bool detectColorCalibrationCard(bool showDebugFrame=false);
        string queryTokens(string jsonStr);
    };
}

#endif