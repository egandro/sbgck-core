CONFIGURE_FILE( base.hpp.in ${CMAKE_SOURCE_DIR}/tests/base.hpp )

# IF( CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
#   # Ignore warnings related to the GNU statement expressions if we
#   # compile with clang.
#   ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-Wno-gnu-statement-expression" )
# ENDIF()

# # Optimizes for a useful debugging experience. While the test cases
# # might run slightly faster if "real" optimizations were enabled, I
# # like this flag for debugging.
# ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-Og" )
# ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-g" )

# #
# # The tests should always have these nasty flags enabled. What's the
# # use of the test without them?
# #
# # Coincidentally, isn't it nice how "-Wall" will not enable any of
# # the flags described afterwards?
# #
# ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-Wall" )
# ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-Wextra" )

# # There are some issues with user-installed libraries in Mac OS X that
# # cause warnings to appear in code that does *not* belong to Aleph, so
# # I rather want this switch to be disabled.
# #
# # The automated tests under Linux will still have this setting though,
# # so I should not miss too many issues.
# IF( NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )
#   ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-Werror" )
# ENDIF()

# ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-Wconversion" )
# ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-Wnon-virtual-dtor" )
# ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-Wold-style-cast" )
# ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-Woverloaded-virtual" )
# ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-Wself-init" )
# ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-Wunsafe-loop-optimization" )

# ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-pedantic" )

set(CMAKE_CXX_STANDARD 17)
#set(OpenCV_STATIC ON)
find_package(OpenCV REQUIRED)

if(UNIX AND NOT APPLE)
    # on Linux
    set(SYSTEM_LIBRARIES stdc++fs pthread asound) # required for filesystem streams on g++
endif()

if(DEFINED EXTERNAL_INSTALL_LOCATION)
    set(EXTERNAL_INSTALL_LOCATION ${EXTERNAL_INSTALL_LOCATION})
else()
    set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
endif()
#message("using EXTERNAL_INSTALL_LOCATION: ${EXTERNAL_INSTALL_LOCATION}")

include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib ${EXTERNAL_INSTALL_LOCATION}/lib64)

include_directories( ${OpenCV_INCLUDE_DIRS}  "../tests/" "../src/" "../include/" )
file(GLOB SOURCE_FILES "../src/*.hpp" "../include/*.hpp")

# https://stackoverflow.com/questions/21394768/cmake-cannot-find-test-if-cmake-runtime-output-directory-is-changed
macro (create_test target)
  add_executable(${target} ${target}.cpp)
  add_test (NAME ${target} COMMAND $<TARGET_FILE:${target}>)
  target_link_libraries(${target} ${OpenCV_LIBS} sbgck_core sbgck_opencv soloud ${SYSTEM_LIBRARIES})
endmacro (create_test)

create_test(test_cameramanager)
create_test(test_componentmanager)
create_test(test_engine)
create_test(test_filemanager)
create_test(test_querytoken)
create_test(test_soundmanager)
