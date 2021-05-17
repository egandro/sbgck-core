#ifndef _COMPONENTMANAGER_HPP
#define _COMPONENTMANAGER_HPP

#include <vector>
#include <regex>
#include <nlohmann/json.hpp>
#include <sbgck_opencv/log.hpp>
#include <sbgck_opencv/board.hpp>
#include <sbgck_opencv/token.hpp>

#include "filemanager.hpp"

namespace SBGCK
{
    class ComponentManager
    {
        ComponentManager(const ComponentManager &value) {}
        vector<Board> boards;

    public:
        ComponentManager() {}

        ~ComponentManager() {}

        bool loadBoard(const unsigned char *imageData,
                       const int imageDataLen,
                       string boardMapJson = "", string boardName = "")
        {
            Log(typelog::INFO) << "ComponentManager loadBoard";
            Asset asset(imageData, imageDataLen);
            if (asset.getDefault().image.empty())
            {
                Log(typelog::ERR) << "ComponentManager loadBoard - asset invalid";
                return false;
            }

            Board board(asset);
            board.name = boardName;

            if (!boardMapJson.empty())
            {
                if (!board.roiManager.initFromJsonString(boardMapJson))
                {
                    Log(typelog::ERR) << "ComponentManager loadBoard - boardMapJson invalid";
                    return false;
                }
            }

            return true;
        }

        bool loadToken(Token &token, const unsigned char *imageData = NULL,
                       const int imageDataLen = 0)
        {
            Log(typelog::INFO) << "ComponentManager loadToken";

            if (imageData != NULL && imageDataLen > 0)
            {
                Asset asset(imageData, imageDataLen);
                if (asset.getDefault().image.empty())
                {
                    Log(typelog::ERR) << "ComponentManager loadToken - asset invalid";
                    return false;
                }
                token.asset = asset;
                // make this an asset detector
                token.tokenDetector = TokenDetector::Asset;
                // default detector strategy
                if (token.asset.assetDetector == AssetDetector::None)
                {
                    token.asset.assetDetector = AssetDetector::Feature2D;
                }
            }

            return true;
        }

        bool loadFromComponentFile(FileManager &fm, string gameConfigJsonFile)
        {

            Log(typelog::INFO) << "ComponentManager loadFromComponentFile";

            string jsonStr = fm.readVFSString(gameConfigJsonFile);
            if (jsonStr.empty())
            {

                Log(typelog::ERR) << "ComponentManager loadFromComponentFile - json file not loaded";
                return false;
            }

            nlohmann::json j = nlohmann::json::parse(jsonStr.c_str());

            if (!j["boards"].empty())
            {
                for (nlohmann::json::iterator it = j["boards"].begin(); it != j["boards"].end(); ++it)
                {
                    string name;
                    string asset;
                    string map;

                    if (!(*it)["name"].empty())
                    {
                        name = (*it)["name"].get<std::string>();
                    }
                    if (!(*it)["asset"].empty())
                    {
                        asset = (*it)["asset"].get<std::string>();
                    }
                    if (!(*it)["map"].empty())
                    {
                        map = (*it)["map"].get<std::string>();
                        map = string("boards/") + map;
                        map = fm.readVFSString(map);
                    }

                    if (asset.empty())
                    {
                        return false;
                    }

                    VFSData data;
                    string fileName = string("boards/") + asset;
                    if (!fm.readVFSData(fileName, data))
                    {
                        return false;
                    }

                    if (!loadBoard((unsigned char *)data.content(), data.size(), map, name))
                    {
                        return false;
                    }
                }
            }

            if (!j["tokens"].empty())
            {
                for (nlohmann::json::iterator it = j["tokens"].begin(); it != j["tokens"].end(); ++it)
                {
                    Token token;
                    VFSData data;
                    string tokenGeometry;

                    if ((*it)["geometry"].empty())
                    {
                        return false;
                    }

                    tokenGeometry = (*it)["geometry"].get<std::string>();

                    if (tokenGeometry == "Triangle")
                    {
                        token.geometry = Geometry::Triangle;
                    }
                    else if (tokenGeometry == "Square")
                    {
                        token.geometry = Geometry::Square;
                    }
                    else if (tokenGeometry == "Rect")
                    {
                        token.geometry = Geometry::Rect;
                    }
                    else if (tokenGeometry == "Pentagon")
                    {
                        token.geometry = Geometry::Pentagon;
                    }
                    else if (tokenGeometry == "Hexagon")
                    {
                        token.geometry = Geometry::Hexagon;
                    }
                    else if (tokenGeometry == "Circle")
                    {
                        token.geometry = Geometry::Circle;
                    }
                    if (token.geometry == Geometry::None)
                    {
                        return false;
                    }

                    if (!(*it)["color"].empty())
                    {
                        string color = (*it)["color"].get<std::string>();

                        // strip whitespace
                        std::regex r("\\s+");
                        color = std::regex_replace(color, r, "");

                        std::vector<int> vect;
                        std::stringstream ss(color);

                        for (int i; ss >> i;)
                        {
                            vect.push_back(i);
                            if (ss.peek() == ',')
                                ss.ignore();
                        }

                        // we need to convert this into BGR from RGB
                        token.color = Scalar(vect.at(2), vect.at(1), vect.at(0));
                    }

                    if (!(*it)["name"].empty())
                    {
                        string name = (*it)["name"].get<std::string>();
                        token.name = name;
                    }

                    if (!(*it)["asset"].empty())
                    {
                        string asset = (*it)["asset"].get<std::string>();
                        string fileName = string("asset/") + asset;
                        if (!fm.readVFSData(fileName, data))
                        {
                            return false;
                        }
                    }

                    if (!loadToken(token, (unsigned char *)data.content(), data.size()))
                    {
                        return false;
                    }
                }
            }

            return true;
        }
    };
}
#endif