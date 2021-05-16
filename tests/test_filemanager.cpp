#include "base.hpp"
#include <sbgck_opencv/log.hpp>
#include "filemanager.hpp"

using namespace SBGCK;

structlog LOGCFG = {};

void testPhysicalDirExist(string baseDir, string dirName)
{
  SBGCK_TEST_BEGIN("testPhysicalDirExist");

  FileManager fm;

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.physicalDirExist(baseDir + "/" + dirName) == true);

  SBGCK_TEST_END();
}

void testPhysicalDirNotExist(string baseDir, string dirName)
{
  SBGCK_TEST_BEGIN("testPhysicalDirNotExist");

  FileManager fm;

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.physicalDirExist(baseDir + "/" + dirName) == false);

  SBGCK_TEST_END();
}

void testPhysicalFileExist(string baseDir, string fileName)
{
  SBGCK_TEST_BEGIN("testPhysicalFileExist");

  FileManager fm;

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.physicalFileExist(baseDir + "/" + fileName) == true);

  SBGCK_TEST_END();
}

void testPhysicalFileNotExist(string baseDir, string fileName)
{
  SBGCK_TEST_BEGIN("testPhysicalFileNotExist");

  FileManager fm;

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.physicalFileExist(baseDir + "/" + fileName) == false);

  SBGCK_TEST_END();
}

void testOpenVFS(string baseDir, string dirName)
{
  SBGCK_TEST_BEGIN("testOpenVFS");

  FileManager fm;

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.openVFS(dirName) == true);

  SBGCK_TEST_END();
}

void testVFSDirExist(string baseDir, string dirName, string vfsGameDir)
{
  SBGCK_TEST_BEGIN("testVFSDirExist");

  FileManager fm;

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.openVFS(dirName) == true);
  SBGCK_ASSERT_THROW(fm.gameDirExist(vfsGameDir) == true);

  SBGCK_TEST_END();
}

void testVFSDirNotExist(string baseDir, string dirName, string vfsGameDir)
{
  SBGCK_TEST_BEGIN("testVFSDirNotExist");

  FileManager fm;

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.openVFS(dirName) == true);
  SBGCK_ASSERT_THROW(fm.gameDirExist(vfsGameDir) == false);

  SBGCK_TEST_END();
}


void testVFSFileExist(string baseDir, string dirName, string vfsGameFileName)
{
  SBGCK_TEST_BEGIN("testVFSFileExist");

  FileManager fm;

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.openVFS(dirName) == true);
  SBGCK_ASSERT_THROW(fm.gameFileExist(vfsGameFileName) == true);

  SBGCK_TEST_END();
}

void testVFSFileNotExist(string baseDir, string dirName, string vfsGameFileName)
{
  SBGCK_TEST_BEGIN("testVFSFileNotExist");

  FileManager fm;

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.openVFS(dirName) == true);
  SBGCK_ASSERT_THROW(fm.gameFileExist(vfsGameFileName) == false);

  SBGCK_TEST_END();
}

void testVFSReadString(string baseDir, string dirName, string vfsGameFileName, string startsWith)
{
  SBGCK_TEST_BEGIN("testVFSReadString");

  FileManager fm;

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.openVFS(dirName) == true);
  string str = fm.readVFSString(vfsGameFileName);
  SBGCK_ASSERT_THROW(str.empty() == false);
  SBGCK_ASSERT_THROW(str.rfind(startsWith, 0) == 0); // starts with (newline agnostic)

  SBGCK_TEST_END();
}

void testVFSRead(string baseDir, string dirName, string vfsGameFileName, string startsWith)
{
  SBGCK_TEST_BEGIN("testVFSRead");

  FileManager fm;

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.openVFS(dirName) == true);
  VFSData data;
  SBGCK_ASSERT_THROW(fm.readVFSData(vfsGameFileName, data) == true);
  SBGCK_ASSERT_THROW(data.size() >= (int)startsWith.size());

  for(std::string::size_type i = 0; i < startsWith.size(); ++i) {
      char c = startsWith[i];
      char *str = (char*)data.content();
      SBGCK_ASSERT_THROW(c == str[i]);
  }

  SBGCK_TEST_END();
}



int main(int, char **)
{
  SBGCK_TEST_INIT();
  string baseDir = CMAKE_SOURCE_DIR + string("/tests/games");
  string physicalGameDir = "test_filemanager";
  string physicalFileName = "README.md";

  string vfsGameDir = "dummydir";
  string vfsGameFileName = "dummy.txt";

  LOGCFG.prefix = (char *)"test_filemanager";
  LOGCFG.headers = true;
  LOGCFG.level = typelog::INFO;

  testPhysicalDirExist(baseDir, physicalGameDir);
  testPhysicalDirNotExist(baseDir, "garbage");
  testPhysicalFileExist(baseDir, physicalFileName);
  testPhysicalFileNotExist(baseDir, "garbage.txt");
  testOpenVFS(baseDir, physicalGameDir);
  testVFSDirExist(baseDir, physicalGameDir, vfsGameDir);
  testVFSDirNotExist(baseDir, physicalGameDir, "garbage");
  testVFSFileExist(baseDir, physicalGameDir, vfsGameFileName);
  testVFSFileNotExist(baseDir, physicalGameDir, "garbage.txt");
  testVFSReadString(baseDir, physicalGameDir, vfsGameFileName, "0123456789");
  testVFSRead(baseDir, physicalGameDir, vfsGameFileName, "0123456789");
}