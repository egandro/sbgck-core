// external stuff...

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable : 4996)
#endif

#if defined(__clang__) || defined(__GNUC__)
// https://stackoverflow.com/questions/12842306/suppress-wunknown-pragmas-warning-in-gcc
// for whatever reasons this doesn't work on C++ - https://gcc.gnu.org/bugzilla/show_bug.cgi?id=53431
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wmisleading-indentation"
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

#define ASSETSYS_IMPLEMENTATION
#include <libs/assetsys.h>

#define STRPOOL_IMPLEMENTATION
#include <libs/strpool.h>

#ifdef _WIN32
#pragma warning(pop)
#endif

#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic pop
#endif