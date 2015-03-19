#include <cstdio>
#include <cstdlib>
#include <libgen.h>
#include <string>
#include <iostream>
#include <sstream>
#include <cstring>
#include "image_core.hpp"

Image::Image(const std::string& filePath)
{
    char* dirName = dirname(strdup(filePath.c_str()));
    char* baseName = basename(strdup(filePath.c_str()));
    printf("filePath = %s, dirName = %s, baseName = %s\n", filePath.c_str(), dirName, baseName);
    Magick::InitializeMagick(dirName);
    try {
        mImage = new Magick::Image(baseName);
    } catch (...) {
        printf("Load image fail!\n");
    }
    mImage->filterType();
}

Image::~Image()
{
    if (mImage)
    {
        delete(mImage);
    }
}

bool Image::get_size(size_t& imageSize)
{
    return true;
}

bool Image::set_size(const size_t imageSize)
{
    try {
        mImage->scale(Magick::Geometry(imageSize, imageSize));
    } catch (...) {
        printf("set_size fail!\n");
        return false;
    }
    return true;
}

bool Image::get_quality(unsigned int& imageQuality)
{
    return true;
}

bool Image::set_quality(const unsigned int imageQuality)
{
    mImage->quality(imageQuality);
    return true;
}

bool Image::get_sharpen(double& radius, double& sigma)
{
    return true;
}

bool Image::set_sharpen(const double& radius, const double& sigma)
{
    try {
        mImage->sharpen(radius, sigma);
    } catch (...) {
        printf("set_sharpen fail!\n");
        return false;
    }
    return true;
}

bool Image::save(const std::string& path)
{
    try {
        mImage->write(path);
    } catch (...) {
        printf("save fail!\n");
        return false;
    }
    return true;
}
