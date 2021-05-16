#ifndef _FILEMANAGER_HPP
#define _FILEMANAGER_HPP

#include <libs/assetsys.h>
#include <string>
#include <sbgck_opencv/log.hpp>

namespace SBGCK
{
    class Filemanager
    {
        string baseDir;
        string gameFileOrFolder;
        assetsys_t* assetsys;
        bool initVFS(string gameName);
        void closeVFS();
        bool dirExist(string dirName);
        bool fileExist(string fileName);

    public:
        Filemanager()
            : assetsys(NULL) {
        }

        ~Filemanager() {
            closeVFS();
        }

        bool init(string applicationDir);
        bool attachGame(string gameName);
    };
}

#endif