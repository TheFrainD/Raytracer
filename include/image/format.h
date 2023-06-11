#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace image {

class Format {
public:
    enum class InternalFormat { kJpg, kPng, kBmp };

    explicit Format(const std::string &extension);
    [[nodiscard]] InternalFormat GetFormat() const noexcept;

private:
    static std::unordered_map<InternalFormat, std::vector<std::string>> format_map_;
    InternalFormat internal_format_;
};

}  // namespace image
