#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "image/pixel.h"

namespace image {

enum class ColorSpace {
    kRgb  = 3,
    kRgba = 4,
};

class Image {
public:
    Image(std::uint32_t width, std::uint32_t height, ColorSpace color_space = ColorSpace::kRgb);

    [[nodiscard]] std::uint32_t GetWidth() const noexcept;
    [[nodiscard]] std::uint32_t GetHeight() const noexcept;
    [[nodiscard]] ColorSpace GetColorSpace() const noexcept;
    [[nodiscard]] Pixel GetPixel(std::uint32_t x, std::uint32_t y) const;

    void SetWidth(std::uint32_t width);
    void SetHeight(std::uint32_t height);
    void SetColorSpace(ColorSpace color_space) noexcept;
    void SetPixel(std::uint32_t x, std::uint32_t y, const Pixel &pixel);
    void InsertPixel(const Pixel &pixel) noexcept;

    void Write(const std::string &filename) const;

private:
    std::uint32_t width_;
    std::uint32_t height_;
    ColorSpace color_space_;
    std::vector<std::uint8_t> buffer_;
};

}  // namespace image