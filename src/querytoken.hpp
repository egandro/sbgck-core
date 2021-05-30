#ifndef _QUERYTOKEN_HPP
#define _QUERYTOKEN_HPP

#include <string>
#include <vector>
#include <sbgck_opencv/log.hpp>
#include <nlohmann/json.hpp>

namespace SBGCK
{

    class QueryTokenParam
    {
    public:
        vector<string> ROI;
        int timeout;
        vector<string> names;
        bool showColorDiff;
        bool showAllROIs;
        bool showContours;

        QueryTokenParam()
            : timeout(0), showColorDiff(false), showAllROIs(false), showContours(false)
        {
        }

        QueryTokenParam(const QueryTokenParam &value)
        {
            for (size_t i = 0; i < value.ROI.size(); i++)
            {
                ROI.push_back(value.ROI.at(i));
            }

            timeout = value.timeout;

            for (size_t i = 0; i < value.names.size(); i++)
            {
                names.push_back(value.names.at(i));
            }

            showColorDiff = value.showColorDiff;
            showAllROIs = value.showAllROIs;
            showContours = value.showContours;
        }
    };

    class QueryTokenResultToken
    {
    public:
        string ROI;
        string name;

        QueryTokenResultToken() {}

        QueryTokenResultToken(const QueryTokenResultToken &value) {
            ROI = value.ROI;
            name = value.name;
        }
    };

    class QueryTokenResult
    {
    public:
        string error;
        vector<QueryTokenResultToken> tokens;

        QueryTokenResult() {}

        QueryTokenResult(const QueryTokenResult &value) {
            error = value.error;

            for (size_t i = 0; i < value.tokens.size(); i++)
            {
                tokens.push_back(value.tokens.at(i));
            }
        }
    };

    // json: https://github.com/nlohmann/json#basic-usage
    void to_json(nlohmann::json &j, const QueryTokenParam &from);
    void from_json(const nlohmann::json &j, QueryTokenParam &to);
    void to_json(nlohmann::json &j, const QueryTokenResultToken &from);
    void from_json(const nlohmann::json &j, QueryTokenResultToken &to);
    void to_json(nlohmann::json &j, const QueryTokenResult &from);
    void from_json(const nlohmann::json &j, QueryTokenResult &to);
}

#endif