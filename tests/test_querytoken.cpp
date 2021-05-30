#include "base.hpp"
#include "querytoken.hpp"

using namespace SBGCK;
using namespace nlohmann;

structlog LOGCFG = {};

void testQueryTokenParam()
{
  SBGCK_TEST_BEGIN("testQueryTokenParam");

  json j_input = R"(
    {
      "ROI": [ "regionA", "regionB", "regionC" ],
      "timeout": 100,
      "names": [ "name1", "name2", "name3" ],
      "showColorDiff": true,
      "showAllROIs": false,
      "showContours": true
    }
  )"_json;

  string input = j_input.dump();

  QueryTokenParam queryTokenParam = j_input.get<QueryTokenParam>();
  SBGCK_ASSERT_THROW(queryTokenParam.ROI.size() == 3);
  SBGCK_ASSERT_THROW(queryTokenParam.timeout == 100);
  SBGCK_ASSERT_THROW(queryTokenParam.names.size() == 3);
  SBGCK_ASSERT_THROW(queryTokenParam.showColorDiff == true);
  SBGCK_ASSERT_THROW(queryTokenParam.showAllROIs == false);
  SBGCK_ASSERT_THROW(queryTokenParam.showColorDiff == true);

  json j_output = queryTokenParam;
  string output = j_output.dump();

  SBGCK_ASSERT_THROW(input == output);

  // optional test
  j_input = R"(
    {
      "ROI": [ "regionA", "regionB", "regionC" ],
      "timeout": 100,
      "names": [ "name1", "name2", "name3" ]
    }
  )"_json;

  input = j_input.dump();
  queryTokenParam = j_input.get<QueryTokenParam>();
  SBGCK_ASSERT_THROW(queryTokenParam.ROI.size() == 3);
  SBGCK_ASSERT_THROW(queryTokenParam.timeout == 100);
  SBGCK_ASSERT_THROW(queryTokenParam.names.size() == 3);
  // defaults to false
  SBGCK_ASSERT_THROW(queryTokenParam.showColorDiff == false);
  SBGCK_ASSERT_THROW(queryTokenParam.showAllROIs == false);
  SBGCK_ASSERT_THROW(queryTokenParam.showColorDiff == false);


  SBGCK_TEST_END();
}

void testQueryTokenResultToken()
{
  SBGCK_TEST_BEGIN("testQueryTokenResultToken");

  json j_input = R"(
    {
      "ROI": "regionA",
      "name": "name1"
    }
  )"_json;

  string input = j_input.dump();

  QueryTokenResultToken queryTokenResultToken = j_input.get<QueryTokenResultToken>();
  SBGCK_ASSERT_THROW(queryTokenResultToken.ROI == "regionA");
  SBGCK_ASSERT_THROW(queryTokenResultToken.name == "name1");

  json j_output = queryTokenResultToken;
  string output = j_output.dump();

  SBGCK_ASSERT_THROW(input == output);

  SBGCK_TEST_END();
}

void testQueryTokenResult()
{
  SBGCK_TEST_BEGIN("testQueryTokenResult");

  json j_input = R"(
    {
      "error": "my error",
      "tokens": [
        {
          "ROI": "regionA",
          "name": "name1"
        },
        {
          "ROI": "regionB",
          "name": "name2"
        },
        {
          "ROI": "regionC",
          "name": "name2"
        }
      ]
    }
  )"_json;

  string input = j_input.dump();

  QueryTokenResult queryTokenResult = j_input.get<QueryTokenResult>();
  SBGCK_ASSERT_THROW(queryTokenResult.error == "my error");
  SBGCK_ASSERT_THROW(queryTokenResult.tokens.size() == 3);

  json j_output = queryTokenResult;
  string output = j_output.dump();

  SBGCK_ASSERT_THROW(input == output);

  SBGCK_TEST_END();
}

int main(int, char **)
{
  SBGCK_TEST_INIT();

  LOGCFG.prefix = (char *)"test_querytoken";
  LOGCFG.headers = true;
  LOGCFG.level = typelog::INFO;

  testQueryTokenParam();
  testQueryTokenResultToken();
  testQueryTokenResult();
}
