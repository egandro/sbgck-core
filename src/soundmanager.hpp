#ifndef _SOUNDMANAGER_HPP
#define _SOUNDMANAGER_HPP

#include <string>
#include <sbgck_opencv/log.hpp>
#include <soloud/soloud.h>
#include <soloud/soloud_wav.h>

#include "sbgck.hpp"
#include "filemanager.hpp"

namespace SBGCK
{
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
        bool loaded;
        //  1.0f is "normal"
        float volume;
        // -1 is left, 1 is right
        float pan;
        int handle;

        SampleVFS(const SampleVFS &value) {}

    public:
        SampleVFS() : loaded(false), volume(1.0f), pan(0.0f), handle(0) {}

        ~SampleVFS()
        {
            // memory handling already done
        }

        bool load(Filemanager &fm, Sample &desc);
        bool play(SoundManager &sm);
        bool stop(SoundManager &sm);
    };
}

#endif