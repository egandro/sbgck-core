#ifndef _COMPONENTMANAGER_HPP
#define _COMPONENTMANAGER_HPP

#include <vector>
#include <sbgck_opencv/log.hpp>
#include <sbgck_opencv/board.hpp>
#include <sbgck_opencv/token.hpp>

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
};

#endif