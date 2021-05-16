#include "soundmanager.hpp"
#include <soloud/soloud_thread.h>

using namespace SBGCK;

void SoundManager::testingWait()
{
    // Wait until sounds have finished
    while (soloud.getActiveVoiceCount() > 0)
    {
        // Still going, sleep for a bit
        SoLoud::Thread::sleep(100);
    }
}

bool SampleVFS::load(Filemanager &fm, Sample &desc)
{
    Log(typelog::INFO) << "SampleVFS load";

    if (loaded)
    {
        // bad but we would required the engine as parameter to stop a playing sample
        Log(typelog::ERR) << "SampleVFS load already loaded";
        return false;
    }

    if (!fm.readVFSData(desc.fileName, data))
    {
        Log(typelog::ERR) << "SampleVFS load failed";
        return false;
    }

    loaded = wav.loadMem((const unsigned char *)data.content(), data.size(), false, false) == SoLoud::SO_NO_ERROR;
    if (!loaded)
    {
        Log(typelog::ERR) << "SampleVFS load failed";
        return false;
    }

    wav.setLooping(desc.loop);
    volume = desc.volume;
    pan = desc.pan;
    return true;
}

bool SampleVFS::play(SoundManager &sm)
{
    Log(typelog::INFO) << "SampleVFS play";

    if (!loaded)
    {
        Log(typelog::ERR) << "SampleVFS play no sample loaded";
        return false;
    }

    handle = sm.soloud.play(wav);
    sm.soloud.setVolume(handle, volume);
    sm.soloud.setPan(handle, pan);

    return true;
}

bool SampleVFS::stop(SoundManager &sm)
{
    Log(typelog::INFO) << "SampleVFS stop";

    if (!loaded)
    {
        Log(typelog::ERR) << "SampleVFS play stop sample loaded";
        return false;
    }

    sm.soloud.stop(handle);
    return true;
}