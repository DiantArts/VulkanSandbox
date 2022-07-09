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
