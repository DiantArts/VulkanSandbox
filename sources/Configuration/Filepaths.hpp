#pragma once

namespace vksb::detail::configuration {

///////////////////////////////////////////////////////////////////////////
/// \brief No clue what it does xD
/// \ingroup vulkan
///
/// \include KeyBindings.hpp <KeyBindings.hpp>
///
///////////////////////////////////////////////////////////////////////////
struct Filepaths
{
    ::std::string_view shadersDirectory{ "./Shaders/" };
    ::std::string_view fragmentDirectory{ "Fragment/" };
    ::std::string_view fragmentExtension{ ".spv" };
    ::std::string_view vertexDirectory{ "Vertex/" };
    ::std::string_view vertexExtension{ ".spv" };
};

} // namespace vksb::detail::configuration
