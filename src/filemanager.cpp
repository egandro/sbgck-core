#pragma warning(push)
#pragma warning(disable : 4996)
#define ASSETSYS_IMPLEMENTATION
#include <libs/assetsys.h>
#define STRPOOL_IMPLEMENTATION
#include <libs/strpool.h>
#pragma warning(pop)

#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;

#include "filemanager.hpp"

using namespace SBGCK;

bool Filemanager::initVFS(string gameName)
{
    Log(typelog::INFO) << "Filemanager initVFS: " << gameName;

    return false;
}

void Filemanager::closeVFS()
{
    Log(typelog::INFO) << "Filemanager closeVFS";
    if (assetsys != NULL)
    {
        assetsys_destroy(assetsys);
        assetsys = NULL;
    }
}

bool Filemanager::dirExist(string dirName)
{
    Log(typelog::INFO) << "Filemanager dirExist: " << dirName;
    // https://en.cppreference.com/w/cpp/filesystem/is_directory
    fs::file_status s = fs::status(dirName);
    if(fs::is_directory(s)) {
        return true;
    }
    return false;
}

bool Filemanager::fileExist(string fileName)
{
    Log(typelog::INFO) << "Filemanager fileExist: " << fileName;
    // https://en.cppreference.com/w/cpp/filesystem/is_regular_file
    fs::file_status s = fs::status(fileName);
    if(fs::is_regular_file(s)) {
        ifstream fstream = ifstream(fileName);
        if(fstream.good()) {
            // we can also read
            return true;
        }

    }
    return false;
}

bool Filemanager::init(string applicationDir)
{
    Log(typelog::INFO) << "Filemanager init: " << applicationDir;

    baseDir = applicationDir;
    closeVFS();

    return true;
}

bool Filemanager::attachGame(string gameName)
{
    Log(typelog::INFO) << "Filemanager attachGame: " << gameName;

    // keep this very very simple now
    string fileOrDirectory = baseDir + "/" + gameName;
    if(!dirExist(fileOrDirectory)) {
        fileOrDirectory = fileOrDirectory + ".zip";
        Log(typelog::INFO) << "Filemanager attachGame trying file: " << fileOrDirectory;
        if(!fileExist(fileOrDirectory)) {
            return false;
        }
    }

    assetsys = assetsys_create(0);
    if (assetsys_mount(assetsys, fileOrDirectory.c_str(), "/game") != ASSETSYS_SUCCESS)
    {
        Log(typelog::ERR) << "Filemanager attachGame assetsys_mount failed";
        return false;
    }

    Log(typelog::INFO) << "Filemanager attachGame mounted: " << fileOrDirectory;

    return true;
}