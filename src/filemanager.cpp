#include <algorithm>
#include <filesystem>
#include <fstream>
#include "internal/filemanager.hpp"

extern "C"
{
#include <libs/assetsys.h>
}

using namespace SBGCK;

#define VFS_ROOT_FOLDER "/game"

void FileManager::closeVFS()
{
    Log(typelog::INFO) << "FileManager closeVFS";
    if (assetsys != NULL)
    {
        assetsys_destroy(assetsys);
        assetsys = NULL;
    }
}

bool FileManager::physicalDirExist(string dirName)
{
    // https://en.cppreference.com/w/cpp/filesystem/is_directory

    Log(typelog::INFO) << "FileManager physicalDirExist: " << dirName;
    filesystem::file_status s = filesystem::status(dirName);
    if (filesystem::is_directory(s))
    {
        return true;
    }
    return false;
}

bool FileManager::physicalFileExist(string fileName)
{
    // https://en.cppreference.com/w/cpp/filesystem/is_regular_file

    Log(typelog::INFO) << "FileManager physicalFileExist: " << fileName;
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

bool FileManager::gameDirExist(string dirName)
{
    string path = string(VFS_ROOT_FOLDER) + "/" + dirName;
    int count = assetsys_file_count(assetsys, path.c_str());
    return count > 0;
}

bool FileManager::gameFileExist(string fileName)
{
    string path = string(VFS_ROOT_FOLDER) + "/" + fileName;
    assetsys_file_t file;
    return assetsys_file(assetsys, path.c_str(), &file) == ASSETSYS_SUCCESS;
}

bool FileManager::init(string applicationDir)
{
    replace(applicationDir.begin(), applicationDir.end(), '\\', '/'); // de-windows

    Log(typelog::INFO) << "FileManager init: " << applicationDir;

    if (!physicalDirExist(applicationDir))
    {
        Log(typelog::ERR) << "FileManager init directory does not exists: " << applicationDir;
    }

    baseDir = applicationDir;
    closeVFS();

    return true;
}

bool FileManager::openVFS(string gameName)
{
    Log(typelog::INFO) << "FileManager openVFS: " << gameName;

    closeVFS();

    // keep this very very simple now
    string fileOrDirectory = baseDir + "/" + gameName;

    // try raw directory
    if (!physicalDirExist(fileOrDirectory))
    {
        // try a zip file
        fileOrDirectory = fileOrDirectory + ".zip";
        Log(typelog::INFO) << "FileManager attachGame trying file: " << fileOrDirectory;
        if (!physicalFileExist(fileOrDirectory))
        {
            return false;
        }
    }

    assetsys = assetsys_create(0);
    if (assetsys_mount(assetsys, fileOrDirectory.c_str(), VFS_ROOT_FOLDER) != ASSETSYS_SUCCESS)
    {
        Log(typelog::ERR) << "FileManager attachGame assetsys_mount failed";
        return false;
    }

    Log(typelog::INFO) << "FileManager attachGame mounted: " << fileOrDirectory;

    return true;
}

string FileManager::readVFSString(string vfsFile)
{
    Log(typelog::INFO) << "FileManager readVFSString: " << vfsFile;

    string path = string(VFS_ROOT_FOLDER) + "/" + vfsFile;
    string res;

    assetsys_file_t file;
    if (assetsys_file(assetsys, path.c_str(), &file) != ASSETSYS_SUCCESS)
    {
        return res;
    }

    int size = assetsys_file_size(assetsys, file);
    int resultSize;
    char *content = (char *)malloc(size + 1); // extra space for '\0'

    if (assetsys_file_load(assetsys, file, &resultSize, (void *)content, size) != ASSETSYS_SUCCESS ||
        resultSize != size)
    {
        Log(typelog::ERR) << "FileManager readVFSString failed";
        free(content);
        return res;
    }

    content[size] = '\0'; // zero terminate the text file
    res = string(content);
    free(content);

    return res;
}

bool FileManager::readVFSData(string vfsFile, VFSData &data)
{
    Log(typelog::INFO) << "FileManager readVFSData: " << vfsFile;

    string path = string(VFS_ROOT_FOLDER) + "/" + vfsFile;

    assetsys_file_t file;
    if (assetsys_file(assetsys, path.c_str(), &file) != ASSETSYS_SUCCESS)
    {
        return false;
    }

    int size = assetsys_file_size(assetsys, file);
    int resultSize;
    char *content = (char *)malloc(size);

    if (assetsys_file_load(assetsys, file, &resultSize, (void *)content, size) != ASSETSYS_SUCCESS ||
        resultSize != size)
    {
        Log(typelog::ERR) << "FileManager readVFSString failed";
        free(content);
        return false;
    }

    // no free here - the VFSData will do that
    data.setData(size, content);

    return true;
}

string FileManager::getCacheDir()
{
    Log(typelog::INFO) << "FileManager getCacheDir";

    string cacheDir = baseDir + "/" + "___cache"; // show on top of file explorer

    if (physicalDirExist(cacheDir))
    {
        return cacheDir;
    }

    filesystem::create_directory(cacheDir);

    if (!physicalDirExist(cacheDir))
    {
        Log(typelog::ERR) << "FileManager can't create cache dir: " << cacheDir;
        return "";
    }

    return cacheDir;
}