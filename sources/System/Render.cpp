///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <System/Render.hpp>



struct SimplePushConstantData {
    ::glm::mat4 modelMatrix{ 1.0f };
    ::glm::mat4 normalMatrix{ 1.0f };
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::vksb::system::Render::Render(
    ::vksb::Device& device,
    ::VkRenderPass renderPass,
    ::VkDescriptorSetLayout descriptorSetLayout
)
    : m_device{ device }
{
    this->createPipelineLayout(descriptorSetLayout);
    this->createPipeline(renderPass);
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Rule of 5
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::vksb::system::Render::~Render()
{
    ::vkDestroyPipelineLayout(m_device.device(), m_pipelineLayout, nullptr);
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Basic
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::system::Render::createPipelineLayout(
    ::VkDescriptorSetLayout descriptorSetLayout
)
{
    ::VkPushConstantRange pushConstantRange{};
    pushConstantRange.stageFlags = ::VK_SHADER_STAGE_VERTEX_BIT | ::VK_SHADER_STAGE_FRAGMENT_BIT;
    pushConstantRange.offset = 0;
    pushConstantRange.size = sizeof(::SimplePushConstantData);

    ::std::vector<::VkDescriptorSetLayout> descriptorSetLayouts{ descriptorSetLayout };

    ::VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = ::VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = descriptorSetLayouts.size();
    pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
    pipelineLayoutInfo.pushConstantRangeCount = 1;
    pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;

    if (::vkCreatePipelineLayout(m_device.device(), &pipelineLayoutInfo, nullptr, &m_pipelineLayout) != ::VK_SUCCESS) {
        throw ::std::runtime_error{ "Failed to create pipeline layout.\n" };
    }
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::system::Render::createPipeline(
    ::VkRenderPass renderPass
)
{
    assert(m_pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");

    ::vksb::Pipeline::Configuration pipelineConfig{};
    pipelineConfig.renderPass = renderPass;
    pipelineConfig.pipelineLayout = m_pipelineLayout;
    m_pPipeline = ::std::make_unique<::vksb::Pipeline>(m_device, pipelineConfig, "simple");
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::system::Render::operator()(
    ::vksb::FrameInfo& frameInfo,
    ::vksb::component::Transform3d& transform
) const
{
    ::SimplePushConstantData push{};
    push.modelMatrix = transform.getMatrix();
    push.normalMatrix = transform.getNormalMatrix();

    ::vkCmdPushConstants(
        frameInfo.commandBuffer,
        m_pipelineLayout,
        ::VK_SHADER_STAGE_VERTEX_BIT | ::VK_SHADER_STAGE_FRAGMENT_BIT,
        0,
        sizeof(::SimplePushConstantData),
        &push
    );
    transform.model->bind(frameInfo.commandBuffer);
    transform.model->draw(frameInfo.commandBuffer);
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::system::Render::bind(
    ::vksb::FrameInfo& frameInfo
)
{
    m_pPipeline->bind(frameInfo.commandBuffer);
    ::vkCmdBindDescriptorSets(
        frameInfo.commandBuffer,
        VK_PIPELINE_BIND_POINT_GRAPHICS,
        m_pipelineLayout,
        0,
        1,
        &frameInfo.descriptorSets[frameInfo.frameIndex],
        0,
        nullptr
    );
}
