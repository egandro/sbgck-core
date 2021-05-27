#include <chrono>
#include "base.hpp"
#include <sbgck_opencv/log.hpp>
#include <soloud/soloud_thread.h>
#include "sbgck.hpp"

using namespace SBGCK;

structlog LOGCFG = {};

#define SILENT_TEST_SOUND false

void testEngineInit(string baseDir, string assetFileName)
{
  SBGCK_TEST_BEGIN("testEngineInit");

  Engine engine;
  engine.isAudioTesting = SILENT_TEST_SOUND;
  engine.isCameraTesting = true;

  SBGCK_ASSERT_THROW(engine.init(baseDir, assetFileName) == true);

  SBGCK_TEST_END();
}

void testEngineLoadGame(string baseDir, string gameName, string assetFileName)
{
  SBGCK_TEST_BEGIN("testEngineLoadGame");

  Engine engine;
  engine.isAudioTesting = SILENT_TEST_SOUND;
  engine.isCameraTesting = true;

  SBGCK_ASSERT_THROW(engine.init(baseDir, assetFileName) == true);
  SBGCK_ASSERT_THROW(engine.loadGame(gameName, "en") == true);

  SBGCK_TEST_END();
}

void testEngineSetBoard(string baseDir, string gameName, string assetFileName, string boardName)
{
  SBGCK_TEST_BEGIN("testEngineSetBoard");

  Engine engine;
  engine.isAudioTesting = SILENT_TEST_SOUND;
  engine.isCameraTesting = true;

  SBGCK_ASSERT_THROW(engine.init(baseDir, assetFileName) == true);
  SBGCK_ASSERT_THROW(engine.loadGame(gameName, "en") == true);
  SBGCK_ASSERT_THROW(engine.setBoard(boardName) == true);

  SBGCK_TEST_END();
}

void testEnginePlaySample(string baseDir, string gameName, string assetFileName)
{
  SBGCK_TEST_BEGIN("testEnginePlaySample");

  Engine engine;
  engine.isAudioTesting = SILENT_TEST_SOUND;
  engine.isCameraTesting = true;

  SBGCK_ASSERT_THROW(engine.init(baseDir, assetFileName) == true);
  SBGCK_ASSERT_THROW(engine.loadGame(gameName, "en") == true);
  SBGCK_ASSERT_THROW(engine.playSample("tetsno.ogg") == true);

  SBGCK_TEST_END();
}

void testEnginePlaySampleSync(string baseDir, string gameName, string assetFileName)
{
  SBGCK_TEST_BEGIN("testEnginePlaySampleSync");

  Engine engine;
  engine.isAudioTesting = SILENT_TEST_SOUND;
  engine.isCameraTesting = true;

  SBGCK_ASSERT_THROW(engine.init(baseDir, assetFileName) == true);
  SBGCK_ASSERT_THROW(engine.loadGame(gameName, "en") == true);
  SBGCK_ASSERT_THROW(engine.playSampleSync("tetsno.ogg", false) == true);

  SBGCK_TEST_END();
}

void testEnginePlaySampleSyncTranslated(string baseDir, string gameName, string assetFileName)
{
  SBGCK_TEST_BEGIN("testEnginePlaySampleSyncTranslated");

  Engine engine;
  engine.isAudioTesting = SILENT_TEST_SOUND;
  engine.isCameraTesting = true;

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
  engine.isAudioTesting = SILENT_TEST_SOUND;
  engine.isCameraTesting = true;

  SBGCK_ASSERT_THROW(engine.init(baseDir, assetFileName) == true);
  SBGCK_ASSERT_THROW(engine.loadGame(gameName, "en") == true);
  SBGCK_ASSERT_THROW(engine.playSample("Ove - Earth Is All We Have .ogg") == true);

#if SILENT_TEST_SOUND == false
  // https://stackoverflow.com/questions/19555121/how-to-get-current-timestamp-in-milliseconds-since-1970-just-the-way-java-gets
  uint64_t end =
    std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

  end += 1000 * 10; // 10 sec

  while (true)
  {
    uint64_t now =
      std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    if(now > end) {
      break;
    }

    // wait consume some time
    SoLoud::Thread::sleep(100);
  }
#endif

  SBGCK_ASSERT_THROW(engine.stopAllAudio() == true);

  SBGCK_TEST_END();
}

void testEngineCalibrateReferenceFrame(string baseDir, string gameName, string assetFileName)
{
  SBGCK_TEST_BEGIN("testEngineCalibrateReferenceFrame");

  Engine engine;
  engine.isAudioTesting = SILENT_TEST_SOUND;
  engine.isCameraTesting = true;

  SBGCK_ASSERT_THROW(engine.init(baseDir, assetFileName) == true);
  SBGCK_ASSERT_THROW(engine.loadGame(gameName, "en") == true);
  SBGCK_ASSERT_THROW(engine.calibrateReferenceFrame() == true);

  SBGCK_TEST_END();
}

void testEngineDetectColorCalibrationCard(string baseDir, string gameName, string assetFileName)
{
  SBGCK_TEST_BEGIN("testEngineDetectColorCalibrationCard");

  Engine engine;
  engine.isAudioTesting = SILENT_TEST_SOUND;
  engine.isCameraTesting = true;

  SBGCK_ASSERT_THROW(engine.init(baseDir, assetFileName) == true);
  SBGCK_ASSERT_THROW(engine.loadGame(gameName, "en") == true);
  SBGCK_ASSERT_THROW(engine.detectColorCalibrationCard() == true);

  SBGCK_TEST_END();
}

void testEngineQueryTokens(string baseDir, string gameName, string assetFileName, string inStr, string outString)
{
  SBGCK_TEST_BEGIN("testEngineQueryTokens");

  Engine engine;
  engine.isAudioTesting = SILENT_TEST_SOUND;
  engine.isCameraTesting = true;

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
  string boardName = "Arctic";

  LOGCFG.prefix = (char *)"test_engine";
  LOGCFG.headers = true;
  LOGCFG.level = typelog::INFO;

  testEngineInit(baseDir, frame_png);
  testEngineLoadGame(baseDir, gameName, frame_png);
  testEngineSetBoard(baseDir, gameName, frame_png, boardName);
  testEnginePlaySample(baseDir, gameName, frame_png);
  testEnginePlaySampleSync(baseDir, gameName, frame_png);
  testEnginePlaySampleSyncTranslated(baseDir, gameName, frame_png);
  testEngineStopAllAudio(baseDir, gameName, frame_png);
  testEngineCalibrateReferenceFrame(baseDir, gameName, frame_png);
  testEngineDetectColorCalibrationCard(baseDir, gameName, frame_png);
  testEngineQueryTokens(baseDir, gameName, frame_png, "", "");
}