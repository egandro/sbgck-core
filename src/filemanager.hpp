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
        void closeVFS();

    public:
        Filemanager()
            : assetsys(NULL) {
        }

        ~Filemanager() {
            closeVFS();
        }
        bool physicalDirExist(string dirName);
        bool physicalFileExist(string fileName);
        bool gameDirExist(string dirName);
        bool gameFileExist(string fileName);
        bool init(string applicationDir);
        bool openVFS(string gameName);
    };
}

#endif