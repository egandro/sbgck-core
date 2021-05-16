#include "base.hpp"
#include <sbgck_opencv/log.hpp>
#include <sbgck_opencv/componentmanager.hpp>

#include "filemanager.hpp"

using namespace SBGCK;

structlog LOGCFG = {};

void testComponentManager(string baseDir, string dirName)
{
  SBGCK_TEST_BEGIN("testComponentManager");

  FileManager fm;

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.openVFS(dirName) == true);

  string vfsGameFileName;
  VFSData data;
  // SBGCK_ASSERT_THROW(fm.readVFSData(vfsGameFileName, data) == true);
  // SBGCK_ASSERT_THROW(data.size() > 0);


  SBGCK_TEST_END();
}


int main(int, char **)
{
  SBGCK_TEST_INIT();
  string baseDir = CMAKE_SOURCE_DIR + string("/tests/games");
  string gameName = "test_componentmanager";

  LOGCFG.prefix = (char *)"test_componentmanager";
  LOGCFG.headers = true;
  LOGCFG.level = typelog::INFO;

  testComponentManager(baseDir, gameName);
}