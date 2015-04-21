#include <cstdio>
#include <cstdlib>
#include <libgen.h>
#include <string>
#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "image_control.hpp"
#include "image_core.hpp"

using namespace std;

static std::string remove_prefix(const std::string path)
{
    std::string key="file://";
    std::size_t found = path.find(key);
    if (found != std::string::npos)
    {
        std::string result(path, key.size());
        return result;
    }
    return path;

}

static void get_files_in_directory(const string &directory, std::vector<string> &out)
{
#ifdef WINDOWS
    HANDLE dir;
    WIN32_FIND_DATA file_data;

    if ((dir = FindFirstFile((directory + "/*").c_str(), &file_data)) == INVALID_HANDLE_VALUE)
        return; /* No files found */

    do {
        const string file_name = file_data.cFileName;
        const string full_file_name = directory + "/" + file_name;
        const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

        if (file_name[0] == '.')
            continue;

        if (is_directory)
            continue;

        out.push_back(full_file_name);
    } while (FindNextFile(dir, &file_data));

    FindClose(dir);
#else
    DIR *dir;
    class dirent *ent;
    class stat st;

    dir = opendir(directory.c_str());
    if (dir == 0)
    {
        out.push_back(directory);
        return;
    }
    while ((ent = readdir(dir)) != NULL) {
        const string file_name = ent->d_name;
        const string full_file_name = directory + "/" + file_name;

        if (file_name[0] == '.')
            continue;

        if (stat(full_file_name.c_str(), &st) == -1)
            continue;

        const bool is_directory = (st.st_mode & S_IFDIR) != 0;

        if (is_directory)
        {
            // std::vector<std::string> subDir;
            // get_files_in_directory(full_file_name, subDir);
            // std::vector<std::string> in = out;
            // in.insert(in.end(), subDir.begin(), subDir.end());
            // in.swap(out);
            continue;
        }

        out.push_back(full_file_name);
    }
    closedir(dir);
#endif
} // get_files_in_directory

ImageControl::ImageControl()
{
}

ImageControl::~ImageControl()
{
}

bool ImageControl::resize_all(const std::string& filePath, const std::string& outputPath, const size_t size)
{
    std::string _filePath = remove_prefix(filePath);
    printf("_filePath = %s\n", _filePath.c_str());
    std::vector<std::string> allFilePath;
    get_files_in_directory(_filePath, allFilePath);

    std::string path = remove_prefix(outputPath);
    std::ostringstream oo;
    printf("oo = %s\n", oo.str().c_str());
    system(oo.str().c_str());
    path += "/";

    for (std::vector<std::string>::iterator iter = allFilePath.begin(); iter != allFilePath.end(); ++iter)
    {

        Image image(*iter);
        image.set_size(size);
        image.set_sharpen(0.2, 0.8);
        image.set_quality(100);
        char* baseName = basename(strdup((*iter).c_str()));
        image.save(path + baseName);
    }
    return true;
}
