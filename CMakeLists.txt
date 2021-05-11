cmake_minimum_required (VERSION 3.2 FATAL_ERROR)
project(sbgck_core)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(UNIX AND NOT APPLE)
    # on Linux
    SET ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall" )
    SET ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall" )
endif()

set(CMAKE_CXX_STANDARD 17)

include(ExternalProject)
find_package(OpenCV REQUIRED)

IF(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # idea from here - https://stackoverflow.com/questions/15100351/changing-cmake-cxx-flags-in-project
    SET ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-psabi" )
ENDIF()

if(UNIX AND NOT APPLE)
    # on Linux
    SET ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC" )
    SET ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC" )
endif()

set(EXTERNAL_INSTALL_LOCATION ${CMAKE_ROOT_BINARY_DIR}/external)
include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

# audio backends
if(UNIX AND NOT APPLE)
    # on Linux
    set (SOLOUD_BACKEND "-DSOLOUD_BACKEND_ALSA=ON")
    link_directories(${EXTERNAL_INSTALL_LOCATION}/lib64)
endif()
if(WIN32)
    set (SOLOUD_BACKEND "-DSOLOUD_BACKEND_WINMM=ON")
endif()
if(APPLE)
    set (SOLOUD_BACKEND "-DSOLOUD_BACKEND_COREAUDIO=ON")
endif()

ExternalProject_Add(soloud_lib
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/soloud/contrib
    CMAKE_ARGS -DSOLOUD_BACKEND_SDL2=OFF -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION} ${SOLOUD_BACKEND}
)

ExternalProject_Add(sbgck_opencv_lib
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/sbgck-opencv
    CMAKE_ARGS -DBUILD_TESTING=OFF -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)

ExternalProject_Add(libs_lib
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)

include_directories( ${OpenCV_INCLUDE_DIRS} "./src/" "./include/" )
file(GLOB SOURCE_FILES "./src/*.cpp" "./src/*.hpp" "./include/*.hpp" )

add_library(sbgck_core STATIC ${SOURCE_FILES})
target_include_directories(sbgck_core PUBLIC include)

add_dependencies(${PROJECT_NAME} soloud_lib)
add_dependencies(${PROJECT_NAME} sbgck_opencv_lib)
add_dependencies(${PROJECT_NAME} libs_lib)

install(TARGETS sbgck_core
        INCLUDES DESTINATION include
        ARCHIVE DESTINATION lib)

install(FILES "include/log.hpp" "include/version.hpp" DESTINATION include/sbgck_opencv)

########################################################################
# Tests - idea https://bastian.rieck.me/blog/posts/2017/simple_unit_tests/
########################################################################

# Enable testing globally. Individual tests may be found in the `tests`
# subdirectory of the repository.
# ENABLE_TESTING()
# ADD_SUBDIRECTORY(tests)

