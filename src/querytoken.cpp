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
        {"names", json::array()},
        {"showColorDiff", from.showColorDiff},
        {"showAllROIs", from.showAllROIs},
        {"showContours", from.showContours}};

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
    for (size_t i = 0; i < j["ROI"].size(); i++)
    {
        string roi = j["ROI"][i].get<std::string>();
        to.ROI.push_back(roi);
    }

    j.at("timeout").get_to(to.timeout);

    for (size_t i = 0; i < j["names"].size(); i++)
    {
        string roi = j["names"][i].get<std::string>();
        to.names.push_back(roi);
    }

    // optional
    if (j.find("showColorDiff") != j.end())
    {
        j.at("showColorDiff").get_to(to.showColorDiff);
    }
    // optional
    if (j.find("showAllROIs") != j.end())
    {
        j.at("showAllROIs").get_to(to.showAllROIs);
    }
    // optional
    if (j.find("showContours") != j.end())
    {
        j.at("showContours").get_to(to.showContours);
    }
}

void SBGCK::to_json(json &j, const QueryTokenResultToken &from)
{
    j = json{
        {"ROI", from.ROI},
        {"name", from.name}};
}

void SBGCK::from_json(const json &j, QueryTokenResultToken &to)
{
    j.at("ROI").get_to(to.ROI);
    j.at("name").get_to(to.name);
}

void SBGCK::to_json(json &j, const QueryTokenResult &from)
{
    j = json{
        {"error", from.error},
        {"tokens", json::array()}};

    for (size_t i = 0; i < from.tokens.size(); i++)
    {
        json queryTokenResult = from.tokens.at(i);
        j["tokens"].push_back(queryTokenResult);
    }
}

void SBGCK::from_json(const json &j, QueryTokenResult &to)
{
    j.at("error").get_to(to.error);

    for (size_t i = 0; i < j["tokens"].size(); i++)
    {
        QueryTokenResultToken tokens = j["tokens"][i].get<QueryTokenResultToken>();
        to.tokens.push_back(tokens);
    }
}