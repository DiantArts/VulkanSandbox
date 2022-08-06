///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Vksb/System/PointLight.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::vksb::system::PointLight::PointLight(
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
::vksb::system::PointLight::~PointLight()
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
void ::vksb::system::PointLight::createPipelineLayout(
    ::VkDescriptorSetLayout descriptorSetLayout
)
{
    ::VkPushConstantRange pushConstantRange{};
    pushConstantRange.stageFlags = ::VK_SHADER_STAGE_VERTEX_BIT | ::VK_SHADER_STAGE_FRAGMENT_BIT;
    pushConstantRange.offset = 0;
    pushConstantRange.size = sizeof(::vksb::component::PointLight::PushConstant);

    ::std::vector<::VkDescriptorSetLayout> descriptorSetLayouts{ descriptorSetLayout };

    ::VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = ::VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = descriptorSetLayouts.size();
    pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
    pipelineLayoutInfo.pushConstantRangeCount = 1;
    pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;

    XRN_ASSERT(
        ::vkCreatePipelineLayout(
            m_device.device(), &pipelineLayoutInfo, nullptr, &m_pipelineLayout
        ) == ::VK_SUCCESS,
        "Create pipeline layout"
    );
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::system::PointLight::createPipeline(
    ::VkRenderPass renderPass
)
{
    XRN_SASSERT(m_pipelineLayout != nullptr, "Cannot create pipeline before pipeline layout");

    ::vksb::Pipeline::Configuration pipelineConfig{};
    pipelineConfig.attributeDescriptions.clear();
    pipelineConfig.bindingDescriptions.clear();
    pipelineConfig.renderPass = renderPass;
    pipelineConfig.pipelineLayout = m_pipelineLayout;
    m_pPipeline = ::std::make_unique<::vksb::Pipeline>(m_device, pipelineConfig, "pointLight");
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::system::PointLight::operator()(
    ::vksb::FrameInfo& frameInfo,
    const ::vksb::component::PointLight& pointLight,
    const ::vksb::component::Position& position
) const
{
    ::vksb::component::PointLight::PushConstant pushConstant{ pointLight, position };
    ::vkCmdPushConstants(
        frameInfo.commandBuffer,
        m_pipelineLayout,
        VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
        0,
        sizeof(pushConstant),
        &pushConstant
    );
    ::vkCmdDraw(frameInfo.commandBuffer, 6, 1, 0, 0);
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::system::PointLight::bind(
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

///////////////////////////////////////////////////////////////////////////
void ::vksb::system::PointLight::update(
    ::vksb::FrameInfo& frameInfo,
    ::vksb::component::PointLight& pointLight,
    ::vksb::component::Position& position,
    ::std::size_t lightIndex
)
{
    auto rotation{ ::glm::rotate(::glm::mat4(1.0f), (float)frameInfo.deltaTime.get() / 1000, { 0.0f, -1.0f, 0.0f }) };
    position = ::glm::vec3{ rotation * ::glm::vec4{ ::glm::vec3{ position }, 1.0f } };
    frameInfo.ubo.pointLights[lightIndex] = ::vksb::component::PointLight::PushConstant{ pointLight, position };
}
