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
    // shaders
    ::std::string_view shadersDirectory{ "./Shaders/" };
    ::std::string_view fragmentDirectory{ "Fragment/" };
    ::std::string_view fragmentExtension{ ".spv" };
    ::std::string_view vertexDirectory{ "Vertex/" };
    ::std::string_view vertexExtension{ ".spv" };

    // models
    ::std::string_view modelDirectory{ "./data/Visual/Model/" };
    ::std::string_view modelExtension{ ".obj" };
};

} // namespace vksb::detail::configuration
