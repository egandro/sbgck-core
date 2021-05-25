#include "base.hpp"
#include <sbgck_opencv/log.hpp>
#include "sbgck.hpp"

using namespace SBGCK;

structlog LOGCFG = {};


void testEngineInit(string baseDir, string assetFileName)
{
  SBGCK_TEST_BEGIN("testEngineInit");

  Engine engine;
  engine.isTesting = true;

  SBGCK_ASSERT_THROW(engine.init(baseDir, assetFileName) == true);

  SBGCK_TEST_END();
}

void testEngineLoadGame(string baseDir, string gameName, string assetFileName)
{
  SBGCK_TEST_BEGIN("testEngineLoadGame");

  Engine engine;
  engine.isTesting = true;

  SBGCK_ASSERT_THROW(engine.init(baseDir, assetFileName) == true);
  SBGCK_ASSERT_THROW(engine.loadGame(gameName, "en") == true);

  SBGCK_TEST_END();
}


int main(int, char **)
{
  SBGCK_TEST_INIT();
  string baseDir = CMAKE_SOURCE_DIR + string("/tests/games");
  string gameName = "test_engine";
  string frame_png = CMAKE_SOURCE_DIR + string("/tests/images/frame.png");

  LOGCFG.prefix = (char *)"test_engine";
  LOGCFG.headers = true;
  LOGCFG.level = typelog::INFO;

  testEngineInit(baseDir, frame_png);
  testEngineLoadGame(baseDir, gameName, frame_png);
}