#include "base.hpp"
#include <sbgck_opencv/log.hpp>
#include "filemanager.hpp"
#include "soundmanager.hpp"

using namespace SBGCK;

structlog LOGCFG = {};

#define SILENT_TEST_SOUND true
#define WAIT_FOR_TEST_SOUND true

#if SILENT_TEST_SOUND
#define WAIT_FOR_SOUNDMANAGER(sm)
#else
#if WAIT_FOR_TEST_SOUND
void WAIT_FOR_SOUNDMANAGER(SoundManager &sm) {
    sm.testingWait();
}
#else
#define WAIT_FOR_SOUNDMANAGER(sm)
#endif
#endif

void testVFSReadSample(string baseDir, string dirName, Sample &desc)
{
  SBGCK_TEST_BEGIN("testVFSReadSample");

  Filemanager fm;
  SampleVFS sample;

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.openVFS(dirName) == true);
  SBGCK_ASSERT_THROW(sample.load(fm, desc) == true);

  SBGCK_TEST_END();
}

void testVFSPlaySample(string baseDir, string dirName, Sample &desc)
{
  SBGCK_TEST_BEGIN("testVFSPlaySample");

  Filemanager fm;
  SampleVFS sample;

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.openVFS(dirName) == true);
  SBGCK_ASSERT_THROW(sample.load(fm, desc) == true);

  SoundManager sm;
  SBGCK_ASSERT_THROW(sm.init(SILENT_TEST_SOUND) == true);
  SBGCK_ASSERT_THROW(sample.play(sm) == true);

  WAIT_FOR_SOUNDMANAGER(sm);

  SBGCK_TEST_END();
}

int main(int, char **)
{
  SBGCK_TEST_INIT();
  string baseDir = CMAKE_SOURCE_DIR + string("/tests/games");
  string physicalGameDir = "test_soundmanager";
  string physicalFileName = "README.md";

  Sample tetsno_ogg;
  tetsno_ogg.fileName = "tetsno.ogg";

  Sample tetsno_ogg_left;
  tetsno_ogg_left.fileName = "tetsno.ogg";
  tetsno_ogg_left.pan = -1.0f;

  Sample tetsno_ogg_right;
  tetsno_ogg_right.fileName = "tetsno.ogg";
  tetsno_ogg_right.pan = 1.0f;

  Sample tetsno_ogg_silent;
  tetsno_ogg_silent.fileName = "tetsno.ogg";
  tetsno_ogg_silent.volume = 0.3f;

  LOGCFG.prefix = (char *)"test_soundmanager";
  LOGCFG.headers = true;
  LOGCFG.level = typelog::INFO;

  testVFSReadSample(baseDir, physicalGameDir, tetsno_ogg);
  testVFSPlaySample(baseDir, physicalGameDir, tetsno_ogg);
  testVFSPlaySample(baseDir, physicalGameDir, tetsno_ogg_left);
  testVFSPlaySample(baseDir, physicalGameDir, tetsno_ogg_right);
  testVFSPlaySample(baseDir, physicalGameDir, tetsno_ogg_silent);
}