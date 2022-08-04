#pragma once

#include <xrn/Util.hpp>
#include <Vksb/Ubo.hpp>

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
        ::std::vector<::VkDescriptorSet>& parentDescriptorSets,
        ::vksb::AScene& parentScene
    );

    ::std::size_t frameIndex;
    ::xrn::Time deltaTime;

    ::VkCommandBuffer commandBuffer;
    ::vksb::Ubo ubo;
    ::glm::mat4 projectionView;

    ::std::vector<::VkDescriptorSet>& descriptorSets;

    ::vksb::AScene& scene;
};

} // namespace vksb
