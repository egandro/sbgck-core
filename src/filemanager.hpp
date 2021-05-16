#ifndef _FILEMANAGER_HPP
#define _FILEMANAGER_HPP

#include <libs/assetsys.h>
#include <string>
#include <sbgck_opencv/log.hpp>

namespace SBGCK
{

    class VFSData
    {
        int contentSize;
        void *contentPtr;
        VFSData(const VFSData &value) {}

    public:
        VFSData() : contentSize(0),
                    contentPtr(NULL)
        {
        }

        VFSData(int contentSize) : contentSize(contentSize),
                                   contentPtr(NULL)
        {
        }

        ~VFSData()
        {
            if (contentPtr != NULL)
            {
                free(contentPtr);
            }
        }

        void setData(int size, void *content)
        {
            if (contentPtr != NULL)
            {
                free(contentPtr);
            }
            contentSize = size;
            contentPtr = content;
        }

        int size() { return contentSize; }
        void *content() { return contentPtr; }
    };

    class Filemanager
    {
        string baseDir;
        string gameFileOrFolder;
        assetsys_t *assetsys;
        void closeVFS();

    public:
        Filemanager()
            : assetsys(NULL)
        {
        }

        ~Filemanager()
        {
            closeVFS();
        }
        bool physicalDirExist(string dirName);
        bool physicalFileExist(string fileName);
        bool gameDirExist(string dirName);
        bool gameFileExist(string fileName);
        bool init(string applicationDir);
        bool openVFS(string gameName);
        string readVFSString(string vfsFile);
        bool readVFSData(string vfsFile, VFSData &data);
    };
}

#endif