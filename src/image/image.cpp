#include "image/image.h"

#include <stdexcept>

namespace image {

Image::Image(const std::uint32_t width, const std::uint32_t height, const ColorSpace color_space)
    : color_space_(color_space) {
    if (width_ == 0 || height_ == 0) {
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

}  // namespace image