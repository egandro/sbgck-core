#include "base.hpp"
#include <sbgck_opencv/log.hpp>
#include "filemanager.hpp"

using namespace SBGCK;

structlog LOGCFG = {};

void testDirExists(string baseDir, string dirName)
{
  SBGCK_TEST_BEGIN("testDirExists");

  Filemanager fm;

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.dirExist(baseDir + "/" + dirName) == true);

  SBGCK_TEST_END();
}


void testFileExists(string baseDir, string fileName)
{
  SBGCK_TEST_BEGIN("testFileExists");

  Filemanager fm;

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.fileExist(baseDir + "/" + fileName) == true);

  SBGCK_TEST_END();
}

int main(int, char **)
{
  SBGCK_TEST_INIT();
  string baseDir = CMAKE_SOURCE_DIR + string("/tests/games");
  string gameDir = "testgame";
  string fileName = "README.md";

  LOGCFG.prefix = (char *)"test_filemanager";
  LOGCFG.headers = true;
  LOGCFG.level = typelog::INFO;

  testDirExists(baseDir, gameDir);
  testFileExists(baseDir, fileName);
}