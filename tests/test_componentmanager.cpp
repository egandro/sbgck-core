#include "base.hpp"
#include <sbgck_opencv/log.hpp>
#include "internal/componentmanager.hpp"
#include "internal/filemanager.hpp"

using namespace SBGCK;

structlog LOGCFG = {};

void testComponentManagerSetBoard(string baseDir, string dirName)
{
  SBGCK_TEST_BEGIN("testComponentManagerSetBoard");

  FileManager fm;
  ComponentManager cm;

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.openVFS(dirName) == true);

  string fileName = "board_test.json";

  SBGCK_ASSERT_THROW(cm.loadFromComponentFile(fm, fileName) == true);
  SBGCK_ASSERT_THROW(cm.boards.size() == 3);
  SBGCK_ASSERT_THROW(cm.tokens.size() == 0);
  SBGCK_ASSERT_THROW(cm.gameName == "Board Test");

  SBGCK_ASSERT_THROW(cm.setBoard("Unknown Board", false) == false);
  SBGCK_ASSERT_THROW(cm.setBoard("Board Test 1", false) == true);
  SBGCK_ASSERT_THROW(cm.currentBoard != NULL);

  SBGCK_ASSERT_THROW(cm.currentBoard->roiManager.isRegion("invalid") == false);
  SBGCK_ASSERT_THROW(cm.currentBoard->roiManager.isRegion("#my poly") == true);

  SBGCK_TEST_END();
}

void testComponentManagerLoadToken(string baseDir, string dirName)
{
  SBGCK_TEST_BEGIN("testComponentManagerLoadToken");

  FileManager fm;
  ComponentManager cm;

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.openVFS(dirName) == true);

  string fileName = "token_test.json";

  SBGCK_ASSERT_THROW(cm.loadFromComponentFile(fm, fileName) == true);
  SBGCK_ASSERT_THROW(cm.boards.size() == 0);
  SBGCK_ASSERT_THROW(cm.tokens.size() == 2);
  SBGCK_ASSERT_THROW(cm.gameName == "Token Test");

  SBGCK_ASSERT_THROW(cm.getToken("Invalid") == NULL);
  SBGCK_ASSERT_THROW(cm.getToken("Red Circle") != NULL);

  Token *t = NULL;

  t = cm.getToken("Red Circle");
  SBGCK_ASSERT_THROW(t->asset.getDefault().image.empty() == true);
  SBGCK_ASSERT_THROW(t->geometry == Geometry::Circle);
  // RGB = 255,0,0 - BGR = 0,0,255
  SBGCK_ASSERT_THROW(t->color[0] == 0);
  SBGCK_ASSERT_THROW(t->color[1] == 0);
  SBGCK_ASSERT_THROW(t->color[2] == 255);

  t = cm.getToken("Card Yes");
  SBGCK_ASSERT_THROW(t->asset.getDefault().image.empty() == false);
  SBGCK_ASSERT_THROW(t->geometry == Geometry::None);
  // no color
  SBGCK_ASSERT_THROW(t->color[0] == 0);
  SBGCK_ASSERT_THROW(t->color[1] == 0);
  SBGCK_ASSERT_THROW(t->color[2] == 0);

  SBGCK_TEST_END();
}

void testComponentManagerGameConfig(string baseDir, string dirName)
{
  SBGCK_TEST_BEGIN("testComponentManagerGameConfig");

  FileManager fm;
  ComponentManager cm;

  SBGCK_ASSERT_THROW(fm.init(baseDir) == true);
  SBGCK_ASSERT_THROW(fm.openVFS(dirName) == true);

  string fileName = "gameconfig.json";

  SBGCK_ASSERT_THROW(cm.loadFromComponentFile(fm, fileName) == true);
  SBGCK_ASSERT_THROW(cm.boards.size() == 1);
  SBGCK_ASSERT_THROW(cm.tokens.size() == 32);
  SBGCK_ASSERT_THROW(cm.gameName == "Dev Game");

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

  testComponentManagerSetBoard(baseDir, gameName);
  testComponentManagerLoadToken(baseDir, gameName);
  testComponentManagerGameConfig(baseDir, gameName);
}