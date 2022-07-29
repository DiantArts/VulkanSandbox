//
// Akanya, Engine
// includes/pch
// g++ -x c++-header -Wpedantic -Wall -Wextra -Wno-volatile -Wno-address -Wno-nonnull-compare -std=c++20 -Ofast -pipe -o includes/pch.hpp.gch -Iincludes -Isources -Ilibraries -Iexterns includes/pch.hpp
//

#ifndef ___INCLUDE_GUARD_INCLUDES_PCH_HPP___
#define ___INCLUDE_GUARD_INCLUDES_PCH_HPP___



#include <stack>
#include <vector>
#include <list>
#include <deque>
#include <array>
#include <set>
#include <map>
#include <queue>
#include <unordered_set>
#include <unordered_map>

#include <algorithm>
#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <ranges>
#include <span>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <variant>
#include <thread>
#include <utility>
#include <concepts>
#include <bitset>
#include <initializer_list>
#include <compare>
#include <cstring>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/hash.hpp>

#include <entt/entt.hpp>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define XRN_USE_VALIDATION_LAYERS

using ::std::string_literals::operator""s;
using ::std::literals::string_view_literals::operator""sv;
using ::std::chrono_literals::operator""ms;

// #define PRINT_DEBUG
// #include <Logger.hpp>


inline auto operator<<(
    ::std::ostream& os,
    const ::glm::vec2& vec
) -> ::std::ostream&
{
    os << '[' << vec.x << ", " << vec.y << ']';
    return os;
}

inline auto operator<<(
    ::std::ostream& os,
    const ::glm::vec3& vec
) -> ::std::ostream&
{
    os << '[' << vec.x << ", " << vec.y << ", " << vec.z << ']';
    return os;
}



#endif // ___INCLUDE_GUARD_INCLUDES_PCH_HPP___
