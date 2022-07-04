///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <App.hpp>



struct SimplePushConstantData {
    ::glm::mat2 transform{ 1.0f };
    ::glm::vec2 offset;
    alignas(16) ::glm::vec3 color;
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::vksb::App::App()
{
    this->loadGameOjects();
    this->createPipelineLayout();
    this->createPipeline();
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Rule of 5
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::vksb::App::~App()
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
auto ::vksb::App::run()
    -> ::std::uint8_t
{
    while (!m_window.shouldClose()) {
        m_window.handleEvents();
        if (auto commandBuffer{ m_renderer.beginFrame() }) {
            m_renderer.beginSwapChainRenderPass(commandBuffer);
            this->renderGameObject(commandBuffer);
            m_renderer.endSwapChainRenderPass(commandBuffer);
            m_renderer.endFrame();
        }
    }

    ::vkDeviceWaitIdle(m_device.device());
    return 0;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Helpers
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::App::loadGameOjects()
{
    ::std::vector<::vksb::Model::Vertex> m_vertices {
        { { 0.0f, -0.5f }, { 1.0f, 0.0f, 0.0f } },
        { { 0.5f, 0.5f }, { 0.0f, 1.0f, 0.0f } },
        { { -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f } },
    };
    auto model{ ::std::make_shared<::vksb::Model>(m_device, m_vertices) };
    auto triangle{ ::vksb::GameObject{ model } };
    triangle.color = { 0.1f, 0.8f, 0.1f };
    triangle.transform2d.translation.x = 0.2f;
    triangle.transform2d.scale = { 2.0f, 0.5f };
    triangle.transform2d.rotation = 0.25f * ::glm::two_pi<float>();
    m_gameObjects.push_back(::std::move(triangle));
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::App::createPipelineLayout()
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
void ::vksb::App::createPipeline()
{
    assert(m_pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");

    ::vksb::Pipeline::Configuration pipelineConfig{};
    pipelineConfig.renderPass = m_renderer.getSwapChainRenderPass();
    pipelineConfig.pipelineLayout = m_pipelineLayout;
    m_pPipeline = ::std::make_unique<::vksb::Pipeline>(m_device, pipelineConfig, "simple");
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::App::renderGameObject(
    ::VkCommandBuffer commandBuffer
)
{
    m_pPipeline->bind(commandBuffer);
    for (auto& object : m_gameObjects) {
        object.transform2d.rotation = ::glm::mod(object.transform2d.rotation + 0.01f, ::glm::two_pi<float>());

        ::SimplePushConstantData push{};
        push.offset = object.transform2d.translation;
        push.color = object.color;
        push.transform = object.transform2d.getMatrix();

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
