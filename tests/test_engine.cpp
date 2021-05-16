#include "base.hpp"
#include <sbgck_opencv/log.hpp>
#include "sbgck.hpp"

using namespace SBGCK;

structlog LOGCFG = {};


void testEngine(string baseDir, string assetFileName)
{
  SBGCK_TEST_BEGIN("testEngine");

  Engine engine;

  SBGCK_ASSERT_THROW(engine.init(baseDir, assetFileName, true) == true);

  SBGCK_TEST_END();
}


int main(int, char **)
{
  SBGCK_TEST_INIT();
  string baseDir = CMAKE_SOURCE_DIR + string("/tests/games");
  string frame_png = CMAKE_SOURCE_DIR + string("/tests/images/frame.png");

  LOGCFG.prefix = (char *)"test_engine";
  LOGCFG.headers = true;
  LOGCFG.level = typelog::INFO;

  testEngine(baseDir, frame_png);
}