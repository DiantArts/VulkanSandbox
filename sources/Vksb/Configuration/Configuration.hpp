#pragma once

#include <Vksb/Configuration/KeyBindings.hpp>
#include <Vksb/Configuration/Filepaths.hpp>

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
    ::vksb::detail::configuration::Filepaths filepath{};

    // Keys
    ::vksb::detail::configuration::KeyBindings keyBinding{};
    float moveSpeed{ 3.0f };
    ::glm::vec3 sensitivity{ 0.05f }; // used for mouse especially

    // Rotation
    ::glm::vec3 rotateSpeed{ 1.5f }; // when rotating with keys
    static inline constexpr float minPitch{ -89.999f };
    static inline constexpr float maxPitch{ 89.999f };

    // others
    ::std::uint16_t maxFrameRate{ 60 };
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
