#ifndef IMAGE_CORE_HPP
#define IMAGE_CORE_HPP
#include "Magick++.h"

class Image {
public:
    Image(const std::string& filePath);
    ~Image();
    bool get_size(size_t& imageSize);
    bool set_size(const size_t imageSize);
    bool get_quality(unsigned int& imageQuality);
    bool set_quality(const unsigned int imageQuality);
    bool get_sharpen(double& radius, double& sigma);
    bool set_sharpen(const double& radius, const double& sigma);
    bool save(const std::string& path);
private:
    Magick::Image* mImage;
};
#endif //IMAGE_CORE_HPP
