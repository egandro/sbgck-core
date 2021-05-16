#include "base.hpp"
#include <sbgck_opencv/log.hpp>
#include "filemanager.hpp"
#include "soundmanager.hpp"

#include <soloud/soloud_thread.h>

using namespace SBGCK;

structlog LOGCFG = {};

#define SILENT_TEST_SOUND true
#define WAIT_FOR_TEST_SOUND true

#if SILENT_TEST_SOUND
#define WAIT_FOR_SOUNDMANAGER(sm)
#else
#if WAIT_FOR_TEST_SOUND
void WAIT_FOR_SOUNDMANAGER(SoundManager &sm)
{
  sm.testingWait();
}
#else
#define WAIT_FOR_SOUNDMANAGER(sm)
#endif
#endif

void testVFSReadSample(string baseDir, string dirName, Sample &desc)
{
  SBGCK_TEST_BEGIN("testVFSReadSample");

  FileManager fm;
  SoundManager sm;
  SampleVFS sample(&sm);

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.openVFS(dirName) == true);
  SBGCK_ASSERT_THROW(sample.load(fm, desc) == true);

  SBGCK_TEST_END();
}

void testVFSPlaySample(string baseDir, string dirName, Sample &desc)
{
  SBGCK_TEST_BEGIN("testVFSPlaySample");

  FileManager fm;
  SoundManager sm;
  SampleVFS sample(&sm);

  SBGCK_ASSERT_THROW(sm.init(SILENT_TEST_SOUND) == true);

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.openVFS(dirName) == true);
  SBGCK_ASSERT_THROW(sample.load(fm, desc) == true);
  SBGCK_ASSERT_THROW(sample.play() == true);

  WAIT_FOR_SOUNDMANAGER(sm);

  SBGCK_TEST_END();
}

void testVFSPlaySampleParamChanges(string baseDir, string dirName, Sample &desc)
{
  SBGCK_TEST_BEGIN("testVFSPlaySampleParamChanges");

  FileManager fm;
  SoundManager sm;
  SampleVFS sample(&sm);

  SBGCK_ASSERT_THROW(sm.init(SILENT_TEST_SOUND) == true);

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.openVFS(dirName) == true);
  SBGCK_ASSERT_THROW(sample.load(fm, desc) == true);
  SBGCK_ASSERT_THROW(sample.play() == true);

#if WAIT_FOR_TEST_SOUND && SILENT_TEST_SOUND==false
  // do some parameter update while playing
  while (sm.soloud.getActiveVoiceCount() > 0)
  {
    // wait consume some time
    SoLoud::Thread::sleep(100);

    if (desc.volume.get() < 1.0f)
    {
      desc.volume.set(desc.volume.get() + 0.05f);
    }

    if (desc.pan.get() < 1.0f)
    {
      desc.pan.set(desc.pan.get() + 0.05f);
    }
  }
#endif

  SBGCK_TEST_END();
}

void testVFSPlayStartStop(string baseDir, string dirName, Sample &desc)
{
  SBGCK_TEST_BEGIN("testVFSPlayStartStop");

  FileManager fm;
  SoundManager sm;
  SampleVFS sample(&sm);

  SBGCK_ASSERT_THROW(sm.init(SILENT_TEST_SOUND) == true);

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.openVFS(dirName) == true);
  SBGCK_ASSERT_THROW(sample.load(fm, desc) == true);
  SBGCK_ASSERT_THROW(sample.play() == true);

#if WAIT_FOR_TEST_SOUND && SILENT_TEST_SOUND==false
  // do some parameter update while playing
  while (sm.soloud.getActiveVoiceCount() > 0)
  {
    // wait consume some time
    SoLoud::Thread::sleep(100);

    if (desc.volume.get() < 1.0f)
    {
      desc.volume.set(desc.volume.get() + 0.05f);
    }

    if (desc.pan.get() < 1.0f)
    {
      // slow increase here, we want 2 sample loops
      desc.pan.set(desc.pan.get() + 0.02f);
    }

    if (desc.pan.get() >= 1.0f)
    {
      // stop
      sample.stop();
    }

    // go on an endless loop
    desc.loop.set(true);
  }
#endif

  SBGCK_TEST_END();
}

void testVFSPlayStopAll(string baseDir, string dirName, Sample &desc)
{
  SBGCK_TEST_BEGIN("testVFSPlayStopAll");

  FileManager fm;
  SoundManager sm;
  SampleVFS sample(&sm);

  SBGCK_ASSERT_THROW(sm.init(SILENT_TEST_SOUND) == true);

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.openVFS(dirName) == true);
  SBGCK_ASSERT_THROW(sample.load(fm, desc) == true);
  SBGCK_ASSERT_THROW(sample.play() == true);

#if WAIT_FOR_TEST_SOUND && SILENT_TEST_SOUND==false
  // do some parameter update while playing
  while (sm.soloud.getActiveVoiceCount() > 0)
  {
    // wait consume some time
    SoLoud::Thread::sleep(100);

    if (desc.volume.get() < 1.0f)
    {
      desc.volume.set(desc.volume.get() + 0.05f);
    }

    if (desc.pan.get() < 1.0f)
    {
      // slow increase here, we want 2 sample loops
      desc.pan.set(desc.pan.get() + 0.02f);
    }

    if (desc.pan.get() >= 1.0f)
    {
      // stop
      sm.stopAll();
    }

    // go on an endless loop
    desc.loop.set(true);
  }
#endif

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

  Sample tetsno_ogg_dynamic_param_changes;
  tetsno_ogg_dynamic_param_changes.fileName = "tetsno.ogg";
  tetsno_ogg_dynamic_param_changes.volume = 0.1f;
  tetsno_ogg_dynamic_param_changes.pan = -1.0f;

  Sample tetsno_ogg_startstop;
  tetsno_ogg_startstop.fileName = "tetsno.ogg";
  tetsno_ogg_startstop.volume = 0.1f;
  tetsno_ogg_startstop.pan = -1.0f;

  LOGCFG.prefix = (char *)"test_soundmanager";
  LOGCFG.headers = true;
  LOGCFG.level = typelog::INFO;

  testVFSReadSample(baseDir, physicalGameDir, tetsno_ogg);
  testVFSPlaySample(baseDir, physicalGameDir, tetsno_ogg);
  testVFSPlaySample(baseDir, physicalGameDir, tetsno_ogg_left);
  testVFSPlaySample(baseDir, physicalGameDir, tetsno_ogg_right);
  testVFSPlaySample(baseDir, physicalGameDir, tetsno_ogg_silent);
  testVFSPlaySampleParamChanges(baseDir, physicalGameDir, tetsno_ogg_dynamic_param_changes);
  testVFSPlayStartStop(baseDir, physicalGameDir, tetsno_ogg_startstop);
  testVFSPlayStopAll(baseDir, physicalGameDir, tetsno_ogg_startstop);
}