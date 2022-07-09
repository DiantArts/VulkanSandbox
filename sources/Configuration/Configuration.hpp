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
    ::vksb::detail::configuration::KeyBindings keyBindings{};
    ::vksb::detail::configuration::Filepaths filepaths{};

    float moveSpeed{ 3.0f };
    float rotateSpeed{ 1.5f }; // when rotating with keys
    static inline constexpr float minPitch{ -89.999f };
    static inline constexpr float maxPitch{ 89.999f };
    static inline constexpr ::glm::vec3 m_sensitivity{ 0.1f, 0.1f, 1.0f };
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
namespace vksb::detail::configuration { extern ::vksb::detail::configuration::Configuration configuration; }
namespace vksb::detail::configuration { extern ::vksb::detail::configuration::Configuration& config; }
namespace vksb::detail { extern ::vksb::detail::configuration::Configuration& config; }
namespace vksb { extern ::vksb::detail::configuration::Configuration& configuration; }
namespace vksb { extern ::vksb::detail::configuration::Configuration& config; }
