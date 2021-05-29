#include "querytoken.hpp"

using namespace SBGCK;
using namespace nlohmann;

// Log(typelog::INFO) << "Engine queryTokens (internal)";

// convert functions - https://github.com/nlohmann/json#basic-usage

void SBGCK::to_json(json &j, const QueryTokenParam &from)
{
    j = json{
        {"ROI", json::array()},
        {"timeout", from.timeout},
        {"names", json::array()}
    };

    for (size_t i = 0; i < from.ROI.size(); i++)
    {
        string roi = from.ROI.at(i);
        j["ROI"].push_back(roi);
    }

    for (size_t i = 0; i < from.names.size(); i++)
    {
        string roi = from.names.at(i);
        j["names"].push_back(roi);
    }
}

void SBGCK::from_json(const nlohmann::json &j, SBGCK::QueryTokenParam &to)
{
    if (j.find("ROI") != j.end())
    {
        for (unsigned int i = 0; i < j["ROI"].size(); i++)
        {
            string roi = j["ROI"][i].get<std::string>();
            to.ROI.push_back(roi);
        }
    }

    if (j.find("timeout") != j.end())
    {
        j.at("timeout").get_to(to.timeout);
    }

    if (j.find("names") != j.end())
    {
        for (unsigned int i = 0; i < j["names"].size(); i++)
        {
            string roi = j["names"][i].get<std::string>();
            to.names.push_back(roi);
        }
    }
}

void SBGCK::to_json(json &j, const QueryTokenResultToken &from)
{
    j = json{
        {"ROI", from.ROI},
        {"name", from.name}
    };
}

void SBGCK::from_json(const json &j, QueryTokenResultToken &to)
{
    if (j.find("ROI") != j.end())
    {
        j.at("ROI").get_to(to.ROI);
    }

    if (j.find("name") != j.end())
    {
        j.at("name").get_to(to.name);
    }
}

void SBGCK::to_json(json &j, const QueryTokenResult &from)
{
    j = json{
        {"error", from.error},
        {"tokens", json::array()}
    };

    for (size_t i = 0; i < from.tokens.size(); i++)
    {
        json queryTokenResult = from.tokens.at(i);
        j["tokens"].push_back(queryTokenResult);
    }
}

void SBGCK::from_json(const json &j, QueryTokenResult &to)
{
    if (j.find("error") != j.end())
    {
        j.at("error").get_to(to.error);
    }

    if (j.find("tokens") != j.end())
    {
        for (unsigned int i = 0; i < j["tokens"].size(); i++)
        {
            QueryTokenResultToken tokens = j["tokens"][i].get<QueryTokenResultToken>();
            to.tokens.push_back(tokens);
        }
    }
}