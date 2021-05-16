#ifndef _SOUNDMANAGER_HPP
#define _SOUNDMANAGER_HPP

#include <string>
#include <sbgck_opencv/log.hpp>
#include <soloud/soloud.h>
#include <soloud/soloud_wav.h>

#include "filemanager.hpp"
#include "property.hpp"

namespace SBGCK
{

    // we might need to move this from here ...

    class Sample
    {
    public:
        string fileName;
        //  1.0f is "normal"
        Property<float> volume;
        // -1 is left, 1 is right
        Property<float> pan;
        // true = loop
        Property<bool> loop;

        Sample() : volume(1.0f),
                   pan(0.0f),
                   loop(false)
        {
        }
    };

    class SoundManager
    {
    public:
        SoLoud::Soloud soloud;

        bool init(bool testing=false)
        {
            int res;

            // keep this simple for now
            if(testing) {
                res = soloud.init(SoLoud::Soloud::CLIP_ROUNDOFF, SoLoud::Soloud::NOSOUND);
            } else {
                res = soloud.init();
            }

            return res == SoLoud::SO_NO_ERROR;
        }

        void testingWait();

        void stopAll() {
            soloud.stopAll();
        }

        ~SoundManager()
        {
            // Clean up SoLoud
            soloud.deinit();
        }
    };

    class SampleVFS
    {
        VFSData data;
        SoLoud::Wav wav;
        float initPan;
        float initVolume;
        bool loaded;
        int handle;
        SoundManager *sm;

        SampleVFS(const SampleVFS &value) {}

    public:
        SampleVFS(SoundManager *sm) : initPan(0.0f), initVolume(1.0f), loaded(false), handle(0), sm(sm) {}

        ~SampleVFS()
        {
            // memory handling already done
        }

        bool load(FileManager &fm, Sample &desc);
        bool play();
        bool stop();
    };
}

#endif