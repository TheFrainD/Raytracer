#include "image/format.h"

#include <algorithm>
#include <stdexcept>

namespace image {

std::unordered_map<Format::InternalFormat, std::vector<std::string>> Format::format_map_ {
    {Format::InternalFormat::kJpg, {"jpg", "jpeg"}},
    {Format::InternalFormat::kPng, {"png"}},
    {Format::InternalFormat::kBmp, {"bmp"}},
};

Format::Format(const std::string& extension) {
    for (auto [format, extension_list] : format_map_) {
        if (std::find(extension_list.begin(), extension_list.end(), extension) != extension_list.end()) {
            internal_format_ = format;
            return;
        }
    }

    throw std::invalid_argument {"Unknown extension"};
}

Format::InternalFormat Format::GetFormat() const noexcept { return internal_format_; }

}  // namespace image
