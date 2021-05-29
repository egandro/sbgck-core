#include "sleep.hpp"
#include <soloud/soloud_thread.h>

void SBGCK::busyWait(int ms) {
    // nice wrapper for Sleep/sleep
    SoLoud::Thread::sleep(1000);
}