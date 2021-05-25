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
            if(isTesting) {
                mode = CameraMode::DebugFile;
            }

            CameraConfig cfg(mode, url);

            return camera.open(cfg);
        }
    };
}

#endif