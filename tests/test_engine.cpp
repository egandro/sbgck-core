#include <chrono>
#include "base.hpp"
#include <sbgck_opencv/log.hpp>
#include <soloud/soloud_thread.h>
#include "sbgck.hpp"

using namespace SBGCK;

structlog LOGCFG = {};

void testEngineInit(string baseDir, string camera)
{
  SBGCK_TEST_BEGIN("testEngineInit");

  Engine engine;

  SBGCK_ASSERT_THROW(engine.init(baseDir, camera) == true);

  SBGCK_TEST_END();
}

void testEngineLoadGame(string baseDir, string gameName, string camera)
{
  SBGCK_TEST_BEGIN("testEngineLoadGame");

  Engine engine;

  SBGCK_ASSERT_THROW(engine.init(baseDir, camera) == true);
  SBGCK_ASSERT_THROW(engine.loadGame(gameName, "en") == true);

  SBGCK_TEST_END();
}

void testEngineSetBoard(string baseDir, string gameName, string camera, string boardName)
{
  SBGCK_TEST_BEGIN("testEngineSetBoard");

  Engine engine;

  SBGCK_ASSERT_THROW(engine.init(baseDir, camera) == true);
  SBGCK_ASSERT_THROW(engine.loadGame(gameName, "en") == true);
  SBGCK_ASSERT_THROW(engine.setBoard(boardName) == true);

  SBGCK_TEST_END();
}

void testEnginePlaySample(string baseDir, string gameName, string camera)
{
  SBGCK_TEST_BEGIN("testEnginePlaySample");

  Engine engine;

  SBGCK_ASSERT_THROW(engine.init(baseDir, camera) == true);
  SBGCK_ASSERT_THROW(engine.loadGame(gameName, "en") == true);
  SBGCK_ASSERT_THROW(engine.playSample("tetsno.ogg") == true);

  SBGCK_TEST_END();
}

void testEnginePlaySampleSync(string baseDir, string gameName, string camera)
{
  SBGCK_TEST_BEGIN("testEnginePlaySampleSync");

  Engine engine;

  SBGCK_ASSERT_THROW(engine.init(baseDir, camera) == true);
  SBGCK_ASSERT_THROW(engine.loadGame(gameName, "en") == true);
  SBGCK_ASSERT_THROW(engine.playSampleSync("tetsno.ogg", false) == true);

  SBGCK_TEST_END();
}

void testEnginePlaySampleSyncTranslated(string baseDir, string gameName, string camera)
{
  SBGCK_TEST_BEGIN("testEnginePlaySampleSyncTranslated");

  Engine engine;

  SBGCK_ASSERT_THROW(engine.init(baseDir, camera) == true);
  SBGCK_ASSERT_THROW(engine.loadGame(gameName, "en") == true);
  SBGCK_ASSERT_THROW(engine.playSampleSync("voice.mp3", true) == true);

  SBGCK_ASSERT_THROW(engine.init(baseDir, camera) == true);
  SBGCK_ASSERT_THROW(engine.loadGame(gameName, "de") == true);
  SBGCK_ASSERT_THROW(engine.playSampleSync("voice.mp3", true) == true);

  SBGCK_ASSERT_THROW(engine.init(baseDir, camera) == true);
  SBGCK_ASSERT_THROW(engine.loadGame(gameName, "fr") == true);
  SBGCK_ASSERT_THROW(engine.playSampleSync("voice.mp3", true) == true);

  SBGCK_TEST_END();
}

void testEngineStopAllAudio(string baseDir, string gameName, string camera)
{
  SBGCK_TEST_BEGIN("testEngineStopAllAudio");

  Engine engine;

  SBGCK_ASSERT_THROW(engine.init(baseDir, camera) == true);
  SBGCK_ASSERT_THROW(engine.loadGame(gameName, "en") == true);
  SBGCK_ASSERT_THROW(engine.playSample("Ove - Earth Is All We Have .ogg") == true);

  if (!engine.isAudioTesting)
  {
    // https://stackoverflow.com/questions/19555121/how-to-get-current-timestamp-in-milliseconds-since-1970-just-the-way-java-gets
    uint64_t end =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    end += 1000 * 10; // 10 sec

    while (true)
    {
      uint64_t now =
          std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

      if (now > end)
      {
        break;
      }

      // wait consume some time
      SoLoud::Thread::sleep(100);
    }
  }

  SBGCK_ASSERT_THROW(engine.stopAllAudio() == true);

  SBGCK_TEST_END();
}

void testEngineCalibrateReferenceFrame(string baseDir, string gameName, string camera)
{
  SBGCK_TEST_BEGIN("testEngineCalibrateReferenceFrame");

  Engine engine;

  SBGCK_ASSERT_THROW(engine.init(baseDir, camera) == true);
  SBGCK_ASSERT_THROW(engine.loadGame(gameName, "en") == true);
  SBGCK_ASSERT_THROW(engine.calibrateReferenceFrame() == false); // no current board set
  SBGCK_ASSERT_THROW(engine.setBoard("Arctic") == true);
  SBGCK_ASSERT_THROW(engine.calibrateReferenceFrame() == true);

  SBGCK_TEST_END();
}

void testEngineDetectColorCalibrationCard(string baseDir, string gameName, string camera)
{
  SBGCK_TEST_BEGIN("testEngineDetectColorCalibrationCard");

  Engine engine;

  SBGCK_ASSERT_THROW(engine.init(baseDir, camera) == true);
  SBGCK_ASSERT_THROW(engine.loadGame(gameName, "en") == true);
  SBGCK_ASSERT_THROW(engine.detectColorCalibrationCard() == true);

  SBGCK_TEST_END();
}

void testEngineQueryTokens(string baseDir, string gameName, string camera, string cameraFrame, string inStr, string outString)
{
  SBGCK_TEST_BEGIN("testEngineQueryTokens");

  Engine engine;

  SBGCK_ASSERT_THROW(engine.init(baseDir, camera) == true);
  SBGCK_ASSERT_THROW(engine.loadGame(gameName, "en") == true);
  SBGCK_ASSERT_THROW(engine.setBoard("Arctic") == true);
  SBGCK_ASSERT_THROW(engine.calibrateReferenceFrame() == true);
  SBGCK_ASSERT_THROW(engine.setTestingCameraFrame(cameraFrame) == true);
  SBGCK_ASSERT_THROW(engine.queryTokens(inStr) == outString);

  SBGCK_TEST_END();
}

int main(int, char **)
{
  SBGCK_TEST_INIT();

  Engine::isAudioTesting = true;
  Engine::isCameraTesting = true;

  string baseDir = CMAKE_SOURCE_DIR + string("/tests/games");
  string gameName = "test_engine_no_camera";
  string camera = baseDir + string("/test_engine_no_camera/boards/frame.png");
  string frame_tokens = baseDir + string("/test_engine_no_camera/boards/frame_tokens.png");

  if (!Engine::isCameraTesting)
  {
    camera = "http://192.168.1.100:8080/video";
    gameName = "test_engine";
  }

  string boardName = "Arctic";

  LOGCFG.prefix = (char *)"test_engine";
  LOGCFG.headers = true;
  LOGCFG.level = typelog::INFO;

  testEngineInit(baseDir, camera);
  testEngineLoadGame(baseDir, gameName, camera);
  testEngineSetBoard(baseDir, gameName, camera, boardName);
  // testEnginePlaySample(baseDir, gameName, camera);
  // testEnginePlaySampleSync(baseDir, gameName, camera);
  // testEnginePlaySampleSyncTranslated(baseDir, gameName, camera);
  // testEngineStopAllAudio(baseDir, gameName, camera);
  testEngineCalibrateReferenceFrame(baseDir, gameName, camera);
  testEngineDetectColorCalibrationCard(baseDir, gameName, camera);
  testEngineQueryTokens(baseDir, gameName, camera, frame_tokens, "", "");
}