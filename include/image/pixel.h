#pragma once

#include <cstdint>

namespace image {

struct Pixel {
    std::uint8_t r;
    std::uint8_t g;
    std::uint8_t b;
    std::uint8_t a;

    Pixel(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 0);
};

}  // namespace image