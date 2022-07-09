///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <System/Render.hpp>



struct SimplePushConstantData {
    ::glm::mat4 transform{ 1.0f };
    alignas(16) ::glm::vec3 color;
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
    ::VkRenderPass renderPass
)
    : m_device{ device }
{
    this->createPipelineLayout();
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
void ::vksb::system::Render::createPipelineLayout()
{
    ::VkPushConstantRange pushConstantRange{};
    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
    pushConstantRange.offset = 0;
    pushConstantRange.size = sizeof(::SimplePushConstantData);

    ::VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;
    pipelineLayoutInfo.pSetLayouts = nullptr;
    pipelineLayoutInfo.pushConstantRangeCount = 1;
    pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;

    if (::vkCreatePipelineLayout(m_device.device(), &pipelineLayoutInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS) {
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
void ::vksb::system::Render::renderGameObjects(
    ::VkCommandBuffer commandBuffer,
    ::std::vector<::vksb::GameObject>& gameObjects,
    const ::vksb::Camera& camera
)
{
    m_pPipeline->bind(commandBuffer);

    auto projectionView{ camera.getProjection() * camera.getView() };

    for (auto& object : gameObjects) {
        object.transform.rotation.y = ::glm::mod(object.transform.rotation.y + 0.01f, ::glm::two_pi<float>());
        object.transform.rotation.x = ::glm::mod(object.transform.rotation.x + 0.005f, ::glm::two_pi<float>());

        ::SimplePushConstantData push{};
        push.color = object.color;
        push.transform = projectionView * object.transform.getMatrix();

        ::vkCmdPushConstants(
            commandBuffer,
            m_pipelineLayout,
            VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
            0,
            sizeof(::SimplePushConstantData),
            &push
        );
        object.model->bind(commandBuffer);
        object.model->draw(commandBuffer);
    }
}
