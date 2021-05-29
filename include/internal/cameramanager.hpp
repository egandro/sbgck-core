#ifndef _CAMERAMANAGER_HPP
#define _CAMERAMANAGER_HPP

#include <string>
#include <regex>
#include <sbgck_opencv/log.hpp>
#include <sbgck_opencv/camera.hpp>

namespace SBGCK
{
    class CameraManager
    {
        Camera camera;


    public:
        bool setTestingCameraFrame(string fileName) {
            return camera.setDebugCameraFrame(fileName);
        }

        bool init(string url = "", bool isTesting = false);

        bool getFrame(Mat &frame);
    };
}

#endif