#ifndef IMAGE_CONTROL_HPP
#define IMAGE_CONTROL_HPP
#include "Magick++.h"

class ImageControl {
public:
    ImageControl();
    ~ImageControl();
    bool resize_all(const std::string& filePath, const std::string& outputPath, const size_t size);
};
#endif //IMAGE_CONTROL_HPP
