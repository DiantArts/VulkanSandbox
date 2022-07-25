#pragma once

#include <xrn/Util.hpp>

namespace vksb { class AScene; }

namespace vksb {

///////////////////////////////////////////////////////////////////////////
/// \brief No clue what it does xD
/// \ingroup vulkan
///
/// \include FrameInfo.hpp <FrameInfo.hpp>
///
///////////////////////////////////////////////////////////////////////////
struct FrameInfo {

    explicit FrameInfo (
        ::vksb::AScene& parentScene
    );

    ::std::size_t frameIndex;
    ::xrn::Time deltaTime;
    ::VkCommandBuffer commandBuffer;
    ::glm::mat4 projectionView;
    ::vksb::AScene& scene;
};

} // namespace vksb
