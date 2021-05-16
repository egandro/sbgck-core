#include "base.hpp"
#include <sbgck_opencv/log.hpp>
#include "filemanager.hpp"

using namespace SBGCK;

structlog LOGCFG = {};

void testPhysicalDirExist(string baseDir, string dirName)
{
  SBGCK_TEST_BEGIN("testPhysicalDirExist");

  Filemanager fm;

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.physicalDirExist(baseDir + "/" + dirName) == true);

  SBGCK_TEST_END();
}

void testPhysicalFileExist(string baseDir, string fileName)
{
  SBGCK_TEST_BEGIN("testPhysicalFileExist");

  Filemanager fm;

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.physicalFileExist(baseDir + "/" + fileName) == true);

  SBGCK_TEST_END();
}

void testOpenVFS(string baseDir, string gameName)
{
  SBGCK_TEST_BEGIN("testOpenVFS");

  Filemanager fm;

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.openVFS(gameName) == true);

  SBGCK_TEST_END();
}

void testVFSDirExist(string baseDir, string dirName, string vfsGameDir)
{
  SBGCK_TEST_BEGIN("testVFSDirExist");

  Filemanager fm;

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.physicalDirExist(baseDir + "/" + dirName) == true);
  SBGCK_ASSERT_THROW(fm.gameDirExist(vfsGameDir) == true);

  SBGCK_TEST_END();
}

void testVFSFileExist(string baseDir, string dirName, string vfsGameFileName)
{
  SBGCK_TEST_BEGIN("testVFSFileExist");

  Filemanager fm;

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.physicalDirExist(baseDir + "/" + dirName) == true);
  SBGCK_ASSERT_THROW(fm.gameFileExist(vfsGameFileName) == true);

  SBGCK_TEST_END();
}

int main(int, char **)
{
  SBGCK_TEST_INIT();
  string baseDir = CMAKE_SOURCE_DIR + string("/tests/games");
  string physicalGameDir = "test_filemanager";
  string physicalFileName = "README.md";

  string vfsGameDir = "mp3s";
  string vfsGameFileName = "dummy.txt";

  LOGCFG.prefix = (char *)"test_filemanager";
  LOGCFG.headers = true;
  LOGCFG.level = typelog::INFO;

  testPhysicalDirExist(baseDir, physicalGameDir);
  testPhysicalFileExist(baseDir, physicalFileName);
  testOpenVFS(baseDir, physicalGameDir);
  testVFSDirExist(baseDir, physicalGameDir, vfsGameDir);
  testVFSFileExist(baseDir, physicalGameDir, vfsGameFileName);
}