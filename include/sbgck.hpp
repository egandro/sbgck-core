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

    class QueryTokenParam
    {
    public:
        vector<string> ROI;
        int timeout;
        vector<string> names;
    };

    class QueryTokenResultToken
    {
    public:
        string ROI;
        string name;
    };

    class QueryTokenResult
    {
    public:
        string error;
        vector<QueryTokenResultToken> tokens;
    };

    class Engine
    {
        string language;

        FileManager fileManager;
        SoundManager soundManager;
        CameraManager cameraManager;
        ComponentManager componentManager;
        void queryTokens(QueryTokenParam &param, QueryTokenResult &result);

    public:
        bool isTesting;

        Engine()
            : isTesting(false)
        {
        }

        //////////////////////////////////////////
        // Management API for UI
        //////////////////////////////////////////

        bool init(string applicationDir, string cameraUrl);
        bool loadGame(string gameName, string lang);

        //////////////////////////////////////////
        // Core Engine API
        //////////////////////////////////////////

        bool setBoard(string boardName);
        bool playSample(string sampleName);
        bool playSampleSync(string sampleName, bool isLocalized);
        bool stopAllAudio();
        bool calibrateReferenceFrame();
        bool detectColorCalibrationCard();
        string queryTokens(string json);
    };
}

#endif