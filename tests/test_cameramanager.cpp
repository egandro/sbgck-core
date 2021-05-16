#include "base.hpp"
#include <sbgck_opencv/log.hpp>
#include "cameramanager.hpp"

using namespace SBGCK;

structlog LOGCFG = {};


void testInitCamera(string assetFileName)
{
  SBGCK_TEST_BEGIN("testInitCamera");

  CameraManager cm;

  SBGCK_ASSERT_THROW(cm.init(assetFileName, true) == true);

  SBGCK_TEST_END();
}


int main(int, char **)
{
  SBGCK_TEST_INIT();
  string frame_png = CMAKE_SOURCE_DIR + string("/tests/images/frame.png");

  testInitCamera(frame_png);
}