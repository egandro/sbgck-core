#include "internal/cameramanager.hpp"
#include "sleep.hpp"

using namespace SBGCK;

bool CameraManager::init(string url, bool isTesting)
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

bool CameraManager::getFrame(Mat &frame)
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
            busyWait(1000);

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