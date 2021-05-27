#ifndef _SOUNDMANAGER_HPP
#define _SOUNDMANAGER_HPP

#include <string>
#include <vector>
#include <sbgck_opencv/log.hpp>
#include <soloud/soloud.h>
#include <soloud/soloud_wav.h>

#include "filemanager.hpp"

namespace SBGCK
{
    class Sample
    {
        Sample(const Sample &value) { }
    public:
        SoLoud::Wav *wav;
        int handle;

        Sample() : wav(NULL), handle(0)
        {
        }

        virtual ~Sample()
        {
            if (wav != NULL)
            {
                delete wav;
                wav = NULL;
            }
        }

        bool load(FileManager &sm, string fileName);
    };

    class SoundManager
    {
        vector<Sample*> samples;
        void cleanStopped();

    public:
        SoLoud::Soloud soloud;

        ~SoundManager()
        {
            for (std::size_t i = 0; i < samples.size(); ++i)
            {
                Sample *sample = samples[i];
                delete sample;
            }

            samples.clear();

            // Clean up SoLoud
            soloud.deinit();
        }

        bool init(bool testing = false)
        {
            int res;

            // keep this simple for now
            if (testing)
            {
                res = soloud.init(SoLoud::Soloud::CLIP_ROUNDOFF, SoLoud::Soloud::NOSOUND);
            }
            else
            {
                res = soloud.init();
            }

            return res == SoLoud::SO_NO_ERROR;
        }

        void stopAll()
        {
            soloud.stopAll();
        }

        bool play(FileManager &fm, string fileName);

        bool playSync(FileManager &fm, string fileName);
    };

}

#endif