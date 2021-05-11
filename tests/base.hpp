#ifndef SBGCK_TESTS_BASE_HH__
#define SBGCK_TESTS_BASE_HH__

#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>

#define CMAKE_SOURCE_DIR         "/home/pi/projects/sbgck/sbgck-core"
#define CMAKE_CURRENT_BINARY_DIR "/home/pi/projects/sbgck/sbgck-core/build/sbgck-opencv/tests"
/* #undef CMAKE_PROJECT_BINARY_DIR */

#define CMAKE_MAJOR_VERSION      "3"
#define CMAKE_MINOR_VERSION      "16"
#define CMAKE_PATCH_VERSION      "3"

#define SBGCK_ASSERT_EQUAL( x, y )                                  \
{                                                                   \
  if( ( x ) != ( y ) )                                              \
  {                                                                 \
    throw std::runtime_error(   std::string( __FILE__ )             \
                              + std::string( ":" )                  \
                              + std::to_string( __LINE__ )          \
                              + std::string( " in " )               \
                              + std::string( __FUNCTION__ )  \
                              + std::string( ": " )                 \
                              + std::to_string( ( x ) )             \
                              + std::string( " != " )               \
                              + std::to_string( ( y ) )             \
    );                                                              \
  }                                                                 \
}


#define SBGCK_ASSERT_THROW( condition )                             \
{                                                                   \
  if( !( condition ) )                                              \
  {                                                                 \
    throw std::runtime_error(   std::string( __FILE__ )             \
                              + std::string( ":" )                  \
                              + std::to_string( __LINE__ )          \
                              + std::string( " in " )               \
                              + std::string( __FUNCTION__ )  \
    );                                                              \
  }                                                                 \
}

#define SBGCK_EXPECT_EXCEPTION( expression, exception )             \
{                                                                   \
  try                                                               \
  {                                                                 \
    ( expression );                                                 \
  }                                                                 \
  catch( exception& e )                                             \
  {                                                                 \
  }                                                                 \
  catch( ... )                                                      \
  {                                                                 \
    throw std::runtime_error(   std::string( __FILE__ )             \
                              + std::string( ":" )                  \
                              + std::to_string( __LINE__ )          \
                              + std::string( " in " )               \
                              + std::string( __FUNCTION__ )  \
    );                                                              \
  }                                                                 \
}

#define SBGCK_TEST_BEGIN( name )\
{\
  std::cerr << "-- Running test \"" << name << "\"...";\
}

#define SBGCK_TEST_END() \
{\
  std::cerr << "finished\n";\
}

#ifdef _WIN32
#include <crtdbg.h>
#include <stdlib.h>
void SBGCK_TEST_INIT() {
    // Suppress the abort message
    _set_abort_behavior( 0, _WRITE_ABORT_MSG);
}
#else
#define SBGCK_TEST_INIT()
#endif

#endif
