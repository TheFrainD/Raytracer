#include "image/image.h"

#include <stdexcept>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include "image/format.h"

namespace image {

Image::Image(const std::uint32_t width, const std::uint32_t height, const ColorSpace color_space)
    : color_space_(color_space) {
    if (width == 0 || height == 0) {
        throw std::invalid_argument {"Width or height cannot be zero"};
    }
    width_  = width;
    height_ = height;
}

std::uint32_t Image::GetWidth() const noexcept { return width_; }

std::uint32_t Image::GetHeight() const noexcept { return height_; }

ColorSpace Image::GetColorSpace() const noexcept { return color_space_; }

Pixel Image::GetPixel(const std::uint32_t x, const std::uint32_t y) const {
    if (x >= width_ || y >= height_) {
        throw std::invalid_argument {"Invalid coordinates for image"};
    }
    const auto index {y * width_ + x};

    switch (color_space_) {
        case ColorSpace::kRgb:
            return {buffer_[index], buffer_[index + 1], buffer_[index + 2]};
        case ColorSpace::kRgba:
            return {buffer_[index], buffer_[index + 1], buffer_[index + 2], buffer_[index + 3]};
    }

    throw std::runtime_error {"Unknown color space"};
}

void Image::SetWidth(const std::uint32_t width) {
    if (width == 0) {
        throw std::invalid_argument {"Width cannot be 0"};
    }
    width_ = width;
}

void Image::SetHeight(const std::uint32_t height) {
    if (height == 0) {
        throw std::invalid_argument {"Height cannot be 0"};
    }
    height_ = height;
}

void Image::SetColorSpace(const ColorSpace color_space) noexcept { color_space_ = color_space; }

void Image::SetPixel(std::uint32_t x, std::uint32_t y, const Pixel& pixel) {
    if (x >= width_ || y >= height_) {
        throw std::invalid_argument {"Invalid coordinates for image"};
    }
    const auto index {y * width_ + x};

    buffer_[index]     = pixel.r;
    buffer_[index + 1] = pixel.g;
    buffer_[index + 2] = pixel.b;
    if (color_space_ == ColorSpace::kRgba) {
        buffer_[index + 3] = pixel.a;
    }
}

void Image::InsertPixel(const Pixel& pixel) noexcept {
    buffer_.push_back(pixel.r);
    buffer_.push_back(pixel.g);
    buffer_.push_back(pixel.b);
    if (color_space_ == ColorSpace::kRgba) {
        buffer_.push_back(pixel.a);
    }
}

void Image::Write(const std::string& filename) const {
    const auto dot_pos {filename.rfind('.')};

    if (dot_pos == std::string::npos || dot_pos == filename.length() - 1) {
        throw std::runtime_error {"Failed to acquire image extension"};
    }

    const auto extension {filename.substr(dot_pos + 1)};
    const auto format = Format(extension);

    const auto comp {static_cast<int>(color_space_)};
    int result {0};
    switch (format.GetFormat()) {
        case Format::InternalFormat::kPng:
            result = stbi_write_png(filename.c_str(), static_cast<int>(width_), static_cast<int>(height_), comp,
                                    buffer_.data(), static_cast<int>(width_ * comp));
            break;
        case Format::InternalFormat::kJpg:
            result = stbi_write_jpg(filename.c_str(), static_cast<int>(width_), static_cast<int>(height_), comp,
                                    buffer_.data(), 100);
            break;
        case Format::InternalFormat::kBmp:
            result = stbi_write_bmp(filename.c_str(), static_cast<int>(width_), static_cast<int>(height_), comp,
                                    buffer_.data());
            break;
    }

    if (result == 0) {
        throw std::runtime_error {"Failed to write the image"};
    }
}

}  // namespace image