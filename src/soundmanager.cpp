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

bool SampleVFS::load(FileManager &fm, Sample &desc)
{
    Log(typelog::INFO) << "SampleVFS load";

    if (handle != 0)
    {
        sm->soloud.stop(handle);
        handle = 0;
    }

    VFSData data;
    if (!fm.readVFSData(desc.fileName, data))
    {
        Log(typelog::ERR) << "SampleVFS load failed";
        return false;
    }

    // copy data to wav. the wave will also free the ram
    loaded = wav.loadMem((const unsigned char *)data.content(), data.size(), true, true) == SoLoud::SO_NO_ERROR;
    if (!loaded)
    {
        Log(typelog::ERR) << "SampleVFS load failed";
        return false;
    }

    wav.setLooping(desc.loop.get());

    // save init volumes
    initVolume = desc.volume.get();
    initPan  = desc.pan.get();

    // we go on signal/slots here
    desc.loop.on_change().connect([this](bool value) {
        wav.setLooping(value);
        if (handle != 0)
        {
            sm->soloud.setLooping(handle, value);
        }
    });

    desc.volume.on_change().connect([this](float value) {
        initVolume = value;
        if (handle != 0)
        {
            sm->soloud.setVolume(handle, value);
        }
    });

    desc.pan.on_change().connect([this](float value) {
        initPan = value;
        if (handle != 0)
        {
            sm->soloud.setPan(handle, value);
        }
    });

    return true;
}

bool SampleVFS::play()
{
    Log(typelog::INFO) << "SampleVFS play";

    if (!loaded)
    {
        Log(typelog::ERR) << "SampleVFS play no sample loaded";
        return false;
    }

    handle = sm->soloud.play(wav, initVolume, initPan);

    return true;
}

bool SampleVFS::stop()
{
    Log(typelog::INFO) << "SampleVFS stop";

    if (!loaded)
    {
        Log(typelog::ERR) << "SampleVFS play stop sample loaded";
        return false;
    }

    sm->soloud.stop(handle);
    return true;
}