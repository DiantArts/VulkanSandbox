#pragma once

namespace vksb {

// from: https://stackoverflow.com/a/57595105
void hashCombine(
    ::std::size_t& seed,
    const auto& v,
    const auto&... rest
)
{
    seed ^= ::std::hash<decltype(v)>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    (hashCombine(seed, rest), ...);
};

}  // namespace vksb
