#include "internal/soundmanager.hpp"
#include <soloud/soloud_thread.h>

using namespace SBGCK;

bool Sample::load(FileManager &fm, string fileName)
{
    Log(typelog::INFO) << "Sample load";

    VFSData data;
    if (!fm.readVFSData(fileName, data))
    {
        Log(typelog::ERR) << "Sample load failed";
        return false;
    }

    if (wav != NULL)
    {
        delete wav;
    }

    // we need this as pointer
    wav = new SoLoud::Wav();

    // copy data to wav-> the wave will also free the ram
    bool loaded = wav->loadMem((const unsigned char *)data.content(), data.size(), true) == SoLoud::SO_NO_ERROR;
    if (!loaded)
    {
        Log(typelog::ERR) << "Sample load failed";
        return false;
    }

    return true;
}

void SoundManager::cleanStopped()
{

    Log(typelog::INFO) << "SoundManager cleanStopped";

    vector<Sample *> deleteList;

    for (std::size_t i = 0; i < samples.size(); ++i)
    {
        Sample *sample = samples[i];
        if (!soloud.isValidVoiceHandle(sample->handle))
        {
            deleteList.push_back(sample);
        }
    }

    for (std::size_t k = 0; k < deleteList.size(); ++k)
    {
        Sample *sample = deleteList[k];

        for (std::size_t i = 0; i < samples.size(); ++i)
        {
            if (sample == samples[i])
            {
                delete sample;
                samples.erase(samples.begin() + (int)i);
                break;
            }
        }
    }
}

void SoundManager::stopAll(int fadeOutTime)
{
    Log(typelog::INFO) << "SoundManager stopAll";

    float volume = soloud.getGlobalVolume();

    soloud.fadeGlobalVolume(0.0f, fadeOutTime);

    if (!isTesting && fadeOutTime > 0)
    {
        // no delay on testing
        SoLoud::Thread::sleep(1000 * (fadeOutTime + 2));
    }

    soloud.stopAll();
    cleanStopped();

    soloud.setGlobalVolume(volume); // restore original volume
}

bool SoundManager::play(FileManager &fm, string fileName)
{
    Log(typelog::INFO) << "SoundManager play " << fileName;

    cleanStopped(); // we have time to do this

    Sample *sample = new Sample();

    if (!sample->load(fm, fileName))
    {
        Log(typelog::ERR) << "Sample load failed";
        delete sample;
        return false;
    }

    sample->handle = soloud.play(*(sample->wav));
    samples.push_back(sample);

    return true;
}

bool SoundManager::playSync(FileManager &fm, string fileName)
{
    Log(typelog::INFO) << "SoundManager play " << fileName;

    cleanStopped(); // we have time to do this

    Sample sample;

    if (!sample.load(fm, fileName))
    {
        Log(typelog::ERR) << "Sample load failed";
        return false;
    }

    sample.handle = soloud.play(*(sample.wav));

    if (!isTesting)
    {
        while (soloud.isValidVoiceHandle(sample.handle))
        {
            // wait consume some time
            SoLoud::Thread::sleep(100);
            // we do an active CPU hold here (may be bad...)
        }
    }

    return true;
}
