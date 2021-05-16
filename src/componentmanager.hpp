#ifndef _COMPONENTMANAGER_HPP
#define _COMPONENTMANAGER_HPP

#include <vector>
#include <sbgck_opencv/log.hpp>
#include <sbgck_opencv/board.hpp>

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
        if( asset.getDefault().image.empty())
            return false;

        Board board(asset);
        board.name = boardName;

        if( !boardMapJson.empty() ) {
            if(!board.roiManager.initFromJsonString(boardMapJson)) {
                Log(typelog::ERR) << "ComponentManager loadBoard - boardMapJson invalid";
                return false;
            }
        }

        return true;
    }
};

#endif