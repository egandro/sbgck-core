#include "base.hpp"
#include <sbgck_opencv/log.hpp>
#include "internal/filemanager.hpp"
#include "internal/soundmanager.hpp"

#include <soloud/soloud_thread.h>

using namespace SBGCK;

structlog LOGCFG = {};

#define SILENT_TEST_SOUND true
#define WAIT_FOR_TEST_SOUND true

void testVFSPlaySample(string baseDir, string dirName, string sampleName)
{
  SBGCK_TEST_BEGIN("testVFSPlaySample");

  FileManager fm;
  SoundManager sm;

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.openVFS(dirName) == true);
  SBGCK_ASSERT_THROW(sm.init(SILENT_TEST_SOUND) == true);

  SBGCK_ASSERT_THROW(sm.play(fm, sampleName) == true);

#if WAIT_FOR_TEST_SOUND == true && SILENT_TEST_SOUND == false
  // do some parameter update while playing
  while (sm.soloud.getActiveVoiceCount() > 0)
  {
    // wait consume some time
    SoLoud::Thread::sleep(100);
  }
#endif

  SBGCK_TEST_END();
}

void testVFSPlaySampleSync(string baseDir, string dirName, string sampleName)
{
  SBGCK_TEST_BEGIN("testVFSPlaySampleSync");

  FileManager fm;
  SoundManager sm;

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.openVFS(dirName) == true);
  SBGCK_ASSERT_THROW(sm.init(SILENT_TEST_SOUND) == true);

  SBGCK_ASSERT_THROW(sm.playSync(fm, sampleName) == true);

  SBGCK_TEST_END();
}

void testVFSPlayStopAll(string baseDir, string dirName, string sampleName)
{
  SBGCK_TEST_BEGIN("testVFSPlayStopAll");

  FileManager fm;
  SoundManager sm;
  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.openVFS(dirName) == true);
  SBGCK_ASSERT_THROW(sm.init(SILENT_TEST_SOUND) == true);

  SBGCK_ASSERT_THROW(sm.play(fm, sampleName) == true);
#if WAIT_FOR_TEST_SOUND == true && SILENT_TEST_SOUND == false
  SoLoud::Thread::sleep(500);
#endif

  SBGCK_ASSERT_THROW(sm.play(fm, sampleName) == true);
#if WAIT_FOR_TEST_SOUND == true && SILENT_TEST_SOUND == false
  SoLoud::Thread::sleep(500);
#endif

  SBGCK_ASSERT_THROW(sm.play(fm, sampleName) == true);
#if WAIT_FOR_TEST_SOUND == true && SILENT_TEST_SOUND == false
  SoLoud::Thread::sleep(500);
#endif

  sm.stopAll();

  SBGCK_TEST_END();
}

int main(int, char **)
{
  SBGCK_TEST_INIT();
  string baseDir = CMAKE_SOURCE_DIR + string("/tests/games");
  string physicalGameDir = "test_soundmanager";
  string physicalFileName = "README.md";

  string tetsno_ogg = "tetsno.ogg";

  LOGCFG.prefix = (char *)"test_soundmanager";
  LOGCFG.headers = true;
  LOGCFG.level = typelog::INFO;

  testVFSPlaySample(baseDir, physicalGameDir, tetsno_ogg);
  testVFSPlaySampleSync(baseDir, physicalGameDir, tetsno_ogg);
  testVFSPlayStopAll(baseDir, physicalGameDir, tetsno_ogg);
}