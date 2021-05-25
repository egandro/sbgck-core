#ifndef _COMPONENTMANAGER_HPP
#define _COMPONENTMANAGER_HPP

#include <vector>
#include <sbgck_opencv/log.hpp>
#include <sbgck_opencv/board.hpp>
#include <sbgck_opencv/token.hpp>

#include "filemanager.hpp"

namespace SBGCK
{
    class ComponentManager
    {
        ComponentManager(const ComponentManager &value) {}

    public:
        vector<Board> boards;
        vector<Token> tokens;

        ComponentManager() {}

        ~ComponentManager() {}

        bool loadBoard(const unsigned char *imageData,
                       const int imageDataLen,
                       string boardMapJson = "", string boardName = "");

        bool loadToken(Token &token, const unsigned char *imageData = NULL,
                       const int imageDataLen = 0);

        bool loadFromComponentFile(FileManager &fm, string gameConfigJsonFile);
    };
}
#endif