#pragma once

namespace vksb {

// from: https://stackoverflow.com/a/57595105
template <
    typename T
> void hashCombine(
    ::std::size_t& seed,
    const T& v,
    const auto&... rest
)
{
    seed ^= ::std::hash<T>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    (hashCombine(seed, rest), ...);
};

}  // namespace vksb
