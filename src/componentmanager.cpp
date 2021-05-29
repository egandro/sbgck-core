#include <regex>
#include <nlohmann/json.hpp>
#include "internal/componentmanager.hpp"

using namespace SBGCK;

void ComponentManager::reset()
{
    // Log(typelog::INFO) << "ComponentManager reset ";
    Log(typelog::WARN) << "ComponentManager reset - NOT implemented";

    gameName = "";
    currentBoard = NULL;
}

bool ComponentManager::readBoardData(const unsigned char *imageData,
                                     const int imageDataLen,
                                     string boardMapJson, string boardName)
{
    Log(typelog::INFO) << "ComponentManager readBoardData";
    Asset asset(imageData, imageDataLen);
    if (asset.getDefault().image.empty())
    {
        Log(typelog::ERR) << "ComponentManager readBoardData - asset invalid";
        return false;
    }

    Board board(asset);
    board.name = boardName;

    if (!boardMapJson.empty())
    {
        if (!board.roiManager.initFromJsonString(boardMapJson))
        {
            Log(typelog::ERR) << "ComponentManager readBoardData - boardMapJson invalid";
            return false;
        }
    }

    boards.push_back(board);

    return true;
}

bool ComponentManager::readTokenData(Token &token, const unsigned char *imageData,
                                     const int imageDataLen)
{
    Log(typelog::INFO) << "ComponentManager readTokenData";

    if (imageData != NULL && imageDataLen > 0)
    {
        Asset asset(imageData, imageDataLen);
        if (asset.getDefault().image.empty())
        {
            Log(typelog::ERR) << "ComponentManager readTokenData - asset invalid";
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

bool ComponentManager::loadFromComponentFile(FileManager &fm, string gameConfigJsonFile)
{
    Log(typelog::INFO) << "ComponentManager loadFromComponentFile";

    reset();

    string jsonStr = fm.readVFSString(gameConfigJsonFile);
    if (jsonStr.empty())
    {
        Log(typelog::ERR) << "ComponentManager loadFromComponentFile - json file not loaded";
        return false;
    }

    nlohmann::json j = nlohmann::json::parse(jsonStr.c_str());

    if (!j["name"].empty())
    {
        gameName = j["name"].get<std::string>();
    }

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
                Log(typelog::ERR) << "ComponentManager loadFromComponentFile - board with empty asset ";
                return false;
            }

            VFSData data;
            string fileName = string("boards/") + asset;
            if (!fm.readVFSData(fileName, data))
            {
                Log(typelog::ERR) << "ComponentManager loadFromComponentFile - board asset loading failed";
                return false;
            }

            if (!readBoardData((unsigned char *)data.content(), data.size(), map, name))
            {
                Log(typelog::ERR) << "ComponentManager loadFromComponentFile - board loadBoard failed";
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

            if (!(*it)["geometry"].empty())
            {
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
                    Log(typelog::ERR) << "ComponentManager loadFromComponentFile - token unknown geometry:" << tokenGeometry;
                    return false;
                }
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

                if (vect.size() != 3)
                {
                    Log(typelog::ERR) << "ComponentManager loadFromComponentFile - token has invalid color: " << color;
                    return false;
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
                string fileName = string("assets/") + asset;
                if (!fm.readVFSData(fileName, data))
                {
                    Log(typelog::ERR) << "ComponentManager loadFromComponentFile - token asset loading failed";
                    return false;
                }
            }

            if (!readTokenData(token, (unsigned char *)data.content(), data.size()))
            {
                Log(typelog::ERR) << "ComponentManager loadFromComponentFile - token loadToken failed";
                return false;
            }

            tokens.push_back(token);
        }
    }
    return true;
}

bool ComponentManager::setBoard(string boardName, bool resetEmptyFrame)
{
    Log(typelog::INFO) << "ComponentManager setBoard " << boardName << " reset empty frame " << resetEmptyFrame;
    currentBoard = NULL;

    for (std::size_t i = 0; i < boards.size(); ++i)
    {
        Board *board = &(boards[i]);
        if (board->name == boardName)
        {
            currentBoard = board;
            if(resetEmptyFrame) {
                currentBoard->frameBoardEmpty = Mat();
            }
            return true;
        }
    }

    return true;
}