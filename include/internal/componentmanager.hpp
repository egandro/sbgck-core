#ifndef _COMPONENTMANAGER_HPP
#define _COMPONENTMANAGER_HPP

#include <vector>
#include <string>
#include <sbgck_opencv/log.hpp>
#include <sbgck_opencv/board.hpp>
#include <sbgck_opencv/token.hpp>
#include <sbgck_opencv/detector.hpp>

#include "filemanager.hpp"

namespace SBGCK
{
    class ComponentManager
    {
        ComponentManager(const ComponentManager &value) {}

        void reset();

        bool readBoardData(const unsigned char *imageData,
                           const int imageDataLen,
                           string boardMapJson = "", string boardName = "");

        bool readTokenData(Token &token, const unsigned char *imageData = NULL,
                           const int imageDataLen = 0);

    public:
        string gameName;
        vector<Board> boards;
        vector<Token> tokens;
        Board *currentBoard;

        ColorMap colorMap;
        Mat colorMapImage;
        std::vector<std::vector<Scalar>> colorMapReferenceColors;
        int colorMapBorder;

        ComponentManager()
            : currentBoard(NULL), colorMapBorder(0) {}

        ~ComponentManager() {}

        bool loadFromComponentFile(FileManager &fm, string gameConfigJsonFile);

        bool setBoard(string boardName, bool resetEmptyFrame);

        Token *getToken(string tokenName)
        {
            for (std::size_t i = 0; i < tokens.size(); ++i)
            {
                Token *token = &(tokens[i]);
                if (token->name == tokenName)
                {
                    return token;
                }
            }
            return NULL;
        }

        void mapTokenColors()
        {
            int i = 0;
            for (vector<Token>::iterator it = tokens.begin(); it != tokens.end(); it++)
            {
                Log(typelog::INFO) << "Mapping Token [" << i << "] from color: " << it->color << " to color: " << colorMap.getMappedColor(it->color);

                it->color = colorMap.getMappedColor(it->color);
                i++;
            }
        }
    };
}
#endif