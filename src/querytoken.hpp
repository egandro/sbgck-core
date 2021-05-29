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
    };

    class QueryTokenResultToken
    {
    public:
        string ROI;
        string name;
    };

    class QueryTokenResult
    {
    public:
        string error;
        vector<QueryTokenResultToken> tokens;
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