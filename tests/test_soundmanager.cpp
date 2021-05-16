#include "base.hpp"
#include <sbgck_opencv/log.hpp>
#include "filemanager.hpp"
#include "soundmanager.hpp"

using namespace SBGCK;

structlog LOGCFG = {};

#define WANT_TEST_SOUND true

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
  SBGCK_ASSERT_THROW(sm.init(WANT_TEST_SOUND) == true);
  SBGCK_ASSERT_THROW(sample.play(sm) == true);

  sm.testingWait();

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

  LOGCFG.prefix = (char *)"test_soundmanager";
  LOGCFG.headers = true;
  LOGCFG.level = typelog::INFO;

  testVFSReadSample(baseDir, physicalGameDir, tetsno_ogg);
  testVFSPlaySample(baseDir, physicalGameDir, tetsno_ogg);
}