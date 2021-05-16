// this is a bit of a crap in windows
#ifdef _WIN32
    #pragma warning(push)
    #pragma warning(disable : 4996)
#endif
#define ASSETSYS_IMPLEMENTATION
#include <libs/assetsys.h>
#define STRPOOL_IMPLEMENTATION
#include <libs/strpool.h>
#ifdef _WIN32
    #pragma warning(pop)
#endif

#include <filesystem>
#include <fstream>
#include "filemanager.hpp"

using namespace SBGCK;

#define VFS_ROOT_FOLDER "/game"

void Filemanager::closeVFS()
{
    Log(typelog::INFO) << "Filemanager closeVFS";
    if (assetsys != NULL)
    {
        assetsys_destroy(assetsys);
        assetsys = NULL;
    }
}

bool Filemanager::physicalDirExist(string dirName)
{
    // https://en.cppreference.com/w/cpp/filesystem/is_directory

    Log(typelog::INFO) << "Filemanager physicalDirExist: " << dirName;
    filesystem::file_status s = filesystem::status(dirName);
    if (filesystem::is_directory(s))
    {
        return true;
    }
    return false;
}

bool Filemanager::physicalFileExist(string fileName)
{
    // https://en.cppreference.com/w/cpp/filesystem/is_regular_file

    Log(typelog::INFO) << "Filemanager physicalFileExist: " << fileName;
    filesystem::file_status s = filesystem::status(fileName);
    if (filesystem::is_regular_file(s))
    {
        ifstream fstream = ifstream(fileName);
        if (fstream.good())
        {
            // we can also read
            return true;
        }
    }
    return false;
}

bool Filemanager::gameDirExist(string dirName)
{
    string path = string(VFS_ROOT_FOLDER) + "/" + dirName;
    int count = assetsys_subdir_count(assetsys, path.c_str());
    return count > 0;
}

bool Filemanager::gameFileExist(string fileName)
{
    string path = string(VFS_ROOT_FOLDER) + "/" + fileName;
    char const *result = assetsys_file_name(assetsys, path.c_str(), 0);
    return result != NULL;
}

bool Filemanager::init(string applicationDir)
{
    Log(typelog::INFO) << "Filemanager init: " << applicationDir;

    if (!physicalDirExist(applicationDir))
    {
        Log(typelog::ERR) << "Filemanager init directory does not exists: " << applicationDir;
    }

    baseDir = applicationDir;
    closeVFS();

    return true;
}

bool Filemanager::openVFS(string gameName)
{
    Log(typelog::INFO) << "Filemanager openVFS: " << gameName;

    closeVFS();

    // keep this very very simple now
    string fileOrDirectory = baseDir + "/" + gameName;

    // try raw directory
    if (!physicalDirExist(fileOrDirectory))
    {
        // try a zip file
        fileOrDirectory = fileOrDirectory + ".zip";
        Log(typelog::INFO) << "Filemanager attachGame trying file: " << fileOrDirectory;
        if (!physicalFileExist(fileOrDirectory))
        {
            return false;
        }
    }

    assetsys = assetsys_create(0);
    if (assetsys_mount(assetsys, fileOrDirectory.c_str(), VFS_ROOT_FOLDER) != ASSETSYS_SUCCESS)
    {
        Log(typelog::ERR) << "Filemanager attachGame assetsys_mount failed";
        return false;
    }

    Log(typelog::INFO) << "Filemanager attachGame mounted: " << fileOrDirectory;

    return true;
}