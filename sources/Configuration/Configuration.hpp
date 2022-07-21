#pragma once

#include <Configuration/KeyBindings.hpp>
#include <Configuration/Filepaths.hpp>

namespace vksb::detail::configuration {

///////////////////////////////////////////////////////////////////////////
/// \brief No clue what it does xD
/// \ingroup vulkan
///
/// \include KeyBindings.hpp <KeyBindings.hpp>
///
///////////////////////////////////////////////////////////////////////////
struct Configuration
{
    ::vksb::detail::configuration::Filepaths filepaths{};

    // Keys
    ::vksb::detail::configuration::KeyBindings keyBindings{};
    float moveSpeed{ 3.0f };
    ::glm::vec3 sensitivity{ 0.1f, 0.1f, 1.0f }; // used for mouse especially

    // Rotation
    ::glm::vec3 rotateSpeed{ 1.5f }; // when rotating with keys
    static inline constexpr float minPitch{ -89.999f };
    static inline constexpr float maxPitch{ 89.999f };
};

} // namespace vksb::detail::configuration



///////////////////////////////////////////////////////////////////////////
// Alias
///////////////////////////////////////////////////////////////////////////
namespace vksb::detail { using Configuration = ::vksb::detail::configuration::Configuration; }
namespace vksb { using Configuration = ::vksb::detail::Configuration; }



///////////////////////////////////////////////////////////////////////////
// Global
///////////////////////////////////////////////////////////////////////////
namespace vksb::detail::configuration {
    extern ::vksb::detail::configuration::Configuration configuration;
    static inline constexpr auto& config{ ::vksb::detail::configuration::configuration };
}
namespace vksb::detail {
    static inline constexpr auto& config{ ::vksb::detail::configuration::configuration };
}
namespace vksb {
    static inline constexpr auto& configuration{ ::vksb::detail::configuration::configuration };
    static inline constexpr auto& config{ ::vksb::detail::configuration::configuration };
}
