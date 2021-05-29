#ifndef _CAMERAMANAGER_HPP
#define _CAMERAMANAGER_HPP

#include <string>
#include <regex>
#include <sbgck_opencv/log.hpp>
#include <sbgck_opencv/camera.hpp>
#include <soloud/soloud_thread.h>

namespace SBGCK
{
    class CameraManager
    {
        Camera camera;


    public:
        bool setTestingCameraFrame(string fileName) {
            return camera.setDebugCameraFrame(fileName);
        }

        bool init(string url = "", bool isTesting = false)
        {
            CameraMode mode = CameraMode::Default;

            // strip whitespace
            std::regex r("\\s+");
            url = std::regex_replace(url, r, "");
            if (!url.empty())
            {
                mode = CameraMode::IPCamera;
            }

            // for testing
            if (isTesting)
            {
                mode = CameraMode::DebugFile;
            }

            CameraConfig cfg(mode, url);

            return camera.open(cfg);
        }

        bool getFrame(Mat &frame)
        {
            int empty = 0;
            int resetCounter = 0;
            while (true)
            {
                if (!camera.getFrame(frame))
                {
                    Log(typelog::DEBUG) << "frame from camera is empty";
                    empty++;

                    // sleep some time to get the camera ready
                    SoLoud::Thread::sleep(1000);

                    if (empty > 3)
                    {
                        Log(typelog::DEBUG) << "can't read from camera - resetting";
                        camera.reset();
                        empty = 0;
                        resetCounter++;
                    }

                    if (resetCounter > 3)
                    {
                        Log(typelog::ERR) << "can't read frame from camera";
                        return false;
                    }
                    continue;
                }
                return true;
            }
        }
    };
}

#endif