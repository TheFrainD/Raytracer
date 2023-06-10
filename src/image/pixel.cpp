#include "image/pixel.h"

namespace image {

Pixel::Pixel(const std::uint8_t r, const std::uint8_t g, const std::uint8_t b, const std::uint8_t a)
    : r(r), g(g), b(b), a(a) {}

}  // namespace image