///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Configuration/Configuration.hpp>



///////////////////////////////////////////////////////////////////////////
// Global
///////////////////////////////////////////////////////////////////////////
namespace vksb::detail::configuration {
    ::vksb::detail::configuration::Configuration configuration{};
    ::vksb::detail::configuration::Configuration& config{ ::vksb::detail::configuration::configuration };
}
namespace vksb::detail {
    ::vksb::detail::configuration::Configuration& config{ ::vksb::detail::configuration::configuration };
}
namespace vksb {
    ::vksb::detail::configuration::Configuration& configuration{ ::vksb::detail::configuration::configuration };
    ::vksb::detail::configuration::Configuration& config{ ::vksb::detail::configuration::configuration };
}
