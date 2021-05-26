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

void testEnginePlaySample(string baseDir, string gameName, string assetFileName)
{
  SBGCK_TEST_BEGIN("testEnginePlaySample");

  Engine engine;
  engine.isTesting = true;

  SBGCK_ASSERT_THROW(engine.init(baseDir, assetFileName) == true);
  SBGCK_ASSERT_THROW(engine.loadGame(gameName, "en") == true);
  SBGCK_ASSERT_THROW(engine.playSample("tetsno.ogg") == true);

  SBGCK_TEST_END();
}

void testEnginePlaySampleSync(string baseDir, string gameName, string assetFileName)
{
  SBGCK_TEST_BEGIN("testEnginePlaySampleSync");

  Engine engine;
  engine.isTesting = true;

  SBGCK_ASSERT_THROW(engine.init(baseDir, assetFileName) == true);
  SBGCK_ASSERT_THROW(engine.loadGame(gameName, "en") == true);
  SBGCK_ASSERT_THROW(engine.playSampleSync("tetsno.ogg", false) == true);

  SBGCK_TEST_END();
}

void testEnginePlaySampleSyncTranslated(string baseDir, string gameName, string assetFileName)
{
  SBGCK_TEST_BEGIN("testEnginePlaySampleSyncTranslated");

  Engine engine;
  engine.isTesting = true;

  SBGCK_ASSERT_THROW(engine.init(baseDir, assetFileName) == true);
  SBGCK_ASSERT_THROW(engine.loadGame(gameName, "en") == true);
  SBGCK_ASSERT_THROW(engine.playSampleSync("voice.mp3", true) == true);

  SBGCK_ASSERT_THROW(engine.init(baseDir, assetFileName) == true);
  SBGCK_ASSERT_THROW(engine.loadGame(gameName, "de") == true);
  SBGCK_ASSERT_THROW(engine.playSampleSync("voice.mp3", true) == true);

  SBGCK_ASSERT_THROW(engine.init(baseDir, assetFileName) == true);
  SBGCK_ASSERT_THROW(engine.loadGame(gameName, "fr") == true);
  SBGCK_ASSERT_THROW(engine.playSampleSync("voice.mp3", true) == true);

  SBGCK_TEST_END();
}

void testEngineStopAllAudio(string baseDir, string gameName, string assetFileName)
{
  SBGCK_TEST_BEGIN("testEngineStopAllAudio");

  Engine engine;
  engine.isTesting = true;

  SBGCK_ASSERT_THROW(engine.init(baseDir, assetFileName) == true);
  SBGCK_ASSERT_THROW(engine.loadGame(gameName, "en") == true);
  SBGCK_ASSERT_THROW(engine.playSample("Ove - Earth Is All We Have .ogg") == true);

  // sleep what so ever....
  // TODO

  SBGCK_ASSERT_THROW(engine.stopAllAudio() == true);

  SBGCK_TEST_END();
}

void testEngineCalibrateReferenceFrame(string baseDir, string gameName, string assetFileName)
{
  SBGCK_TEST_BEGIN("testEngineCalibrateReferenceFrame");

  Engine engine;
  engine.isTesting = true;

  SBGCK_ASSERT_THROW(engine.init(baseDir, assetFileName) == true);
  SBGCK_ASSERT_THROW(engine.loadGame(gameName, "en") == true);
  SBGCK_ASSERT_THROW(engine.calibrateReferenceFrame() == true);

  SBGCK_TEST_END();
}

void testEngineDetectColorCalibrationCard(string baseDir, string gameName, string assetFileName)
{
  SBGCK_TEST_BEGIN("testEngineDetectColorCalibrationCard");

  Engine engine;
  engine.isTesting = true;

  SBGCK_ASSERT_THROW(engine.init(baseDir, assetFileName) == true);
  SBGCK_ASSERT_THROW(engine.loadGame(gameName, "en") == true);
  SBGCK_ASSERT_THROW(engine.detectColorCalibrationCard() == true);

  SBGCK_TEST_END();
}

void testEngineQueryTokens(string baseDir, string gameName, string assetFileName, string inStr, string outString)
{
  SBGCK_TEST_BEGIN("testEngineQueryTokens");

  Engine engine;
  engine.isTesting = true;

  SBGCK_ASSERT_THROW(engine.init(baseDir, assetFileName) == true);
  SBGCK_ASSERT_THROW(engine.loadGame(gameName, "en") == true);
  SBGCK_ASSERT_THROW(engine.queryTokens(inStr) == outString);

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
  testEnginePlaySample(baseDir, gameName, frame_png);
  testEnginePlaySampleSync(baseDir, gameName, frame_png);
  testEnginePlaySampleSyncTranslated(baseDir, gameName, frame_png);
  testEngineStopAllAudio(baseDir, gameName, frame_png);
  testEngineCalibrateReferenceFrame(baseDir, gameName, frame_png);
  testEngineDetectColorCalibrationCard(baseDir, gameName, frame_png);
  testEngineQueryTokens(baseDir, gameName, frame_png, "", "");
}