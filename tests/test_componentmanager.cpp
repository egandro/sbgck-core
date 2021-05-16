#include "base.hpp"
#include <sbgck_opencv/log.hpp>
#include "componentmanager.hpp"
#include "filemanager.hpp"

using namespace SBGCK;

structlog LOGCFG = {};

void testComponentManager(string baseDir, string dirName)
{
  SBGCK_TEST_BEGIN("testComponentManager");

  FileManager fm;
  string fileName;
  VFSData data;

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.openVFS(dirName) == true);

  fileName = "boards/Arctic-base.png";
  SBGCK_ASSERT_THROW(fm.readVFSData(fileName, data) == true);
  SBGCK_ASSERT_THROW(data.size() > 0);

  fileName = "boards/Arctic-base.json";
  string json = fm.readVFSString(fileName);
  SBGCK_ASSERT_THROW(json.empty() == false);

  ComponentManager cm;
  SBGCK_ASSERT_THROW(cm.loadBoard((unsigned char*) data.content(), data.size(), json, "arctic") == true);

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