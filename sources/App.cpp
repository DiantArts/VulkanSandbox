///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <App.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::vksb::App::App()
{
    this->loadModels();
    if (!this->createPipelineLayout() || !this->recreateSwapChain() || !this->createCommandBuffers()) {
        throw ::std::runtime_error{ "unable to create the app" };
    }
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
void ::vksb::App::run()
{
    while (!m_window.shouldClose()) {
        m_window.handleEvents();
        this->drawFrame();
    }

    vkDeviceWaitIdle(m_device.device());
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Helpers
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::App::loadModels()
{
    ::std::vector<::vksb::Model::Vertex> m_vertices {
        { { 0.0f, -0.5f }, { 1.0f, 0.0f, 0.0f } },
        { { 0.5f, 0.5f }, { 0.0f, 1.0f, 0.0f } },
        { { -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f } },
    };
    m_pModel = ::std::make_unique<::vksb::Model>(m_device, m_vertices);
}

///////////////////////////////////////////////////////////////////////////
auto ::vksb::App::createPipelineLayout()
    -> bool
{
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;
    pipelineLayoutInfo.pSetLayouts = nullptr;
    pipelineLayoutInfo.pushConstantRangeCount = 0;
    pipelineLayoutInfo.pPushConstantRanges = nullptr;

    if (::vkCreatePipelineLayout(m_device.device(), &pipelineLayoutInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS) {
        throw ::std::runtime_error{ "Failed to create pipeline layout.\n" };
        return false;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////
auto ::vksb::App::createPipeline()
    -> bool
{
    assert(m_pSwapChain != nullptr && "Cannot create pipeline before swap chain");
    assert(m_pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");

    ::vksb::Pipeline::Configuration pipelineConfig{};
    pipelineConfig.renderPass = m_pSwapChain->getRenderPass();
    pipelineConfig.pipelineLayout = m_pipelineLayout;
    m_pPipeline = ::std::make_unique<::vksb::Pipeline>(m_device, pipelineConfig, "simple");
    return true;
}

///////////////////////////////////////////////////////////////////////////
auto ::vksb::App::createCommandBuffers()
    -> bool
{
    m_commandBuffers.resize(m_pSwapChain->imageCount());

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = m_device.getCommandPool();
    allocInfo.commandBufferCount = static_cast<uint32_t>(m_commandBuffers.size());

    if (vkAllocateCommandBuffers(m_device.device(), &allocInfo, m_commandBuffers.data()) !=
        VK_SUCCESS) {
        throw ::std::runtime_error{ "failed to allocate command buffers!\n" };
        return false;
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::App::freeCommandBuffers()
{
    ::vkFreeCommandBuffers(
        m_device.device(),
        m_device.getCommandPool(),
        static_cast<::std::size_t>(m_commandBuffers.size()),
        m_commandBuffers.data()
    );
    m_commandBuffers.clear();
}

///////////////////////////////////////////////////////////////////////////
auto ::vksb::App::drawFrame()
    -> bool
{
    ::std::uint32_t imageIndex;

    switch (m_pSwapChain->acquireNextImage(&imageIndex)) {
    case VK_SUCCESS:
    case VK_SUBOPTIMAL_KHR:
        break;
    case VK_ERROR_OUT_OF_DATE_KHR:
        ::std::cout << "New swapchain needs to be created." << ::std::endl;
        m_window.setResizedFlag();
        return this->recreateSwapChain();
    default:
        throw ::std::runtime_error{ "Failed to aquire swapChain image.\n" };
        return false;
    }

    this->recordCommandBuffer(imageIndex);
    if (
        auto result{ m_pSwapChain->submitCommandBuffers(&m_commandBuffers[imageIndex], &imageIndex) };
        result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR
    ) {
        m_window.setResizedFlag();
        goto WINDOW_RESIZED;
    } else if (m_window.wasResized()) {
    WINDOW_RESIZED:
        return recreateSwapChain();
    } else {
        throw ::std::runtime_error{ "Failed to present swapChain image.\n" };
        return false;
    }

    // for (auto i{ 0uz }; i < m_commandBuffers.size(); ++i) {}
    return true;
}

///////////////////////////////////////////////////////////////////////////
auto ::vksb::App::recreateSwapChain()
    -> bool
{
    auto windowSize{ m_window.getSize() };
    while (!windowSize.isValid()) {
        windowSize = m_window.getSize();
        ::glfwWaitEvents();
    }
    ::vkDeviceWaitIdle(m_device.device());

    if (!m_pSwapChain) {
        m_pSwapChain = ::std::make_unique<::vksb::SwapChain>(m_device, windowSize);
    } else {
        m_pSwapChain = ::std::make_unique<::vksb::SwapChain>(m_device, windowSize, ::std::move(m_pSwapChain));
        if (m_pSwapChain->imageCount() != m_commandBuffers.size()) {
            this->freeCommandBuffers();
            this->createCommandBuffers();
        }
    }
    if (!this->createPipeline()) {
        throw ::std::runtime_error{ "Failed to create pipeline with the new swapchain.\n" };
        return false;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////
auto ::vksb::App::recordCommandBuffer(
    ::std::size_t imageIndex
) -> bool
{
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if (vkBeginCommandBuffer(m_commandBuffers[imageIndex], &beginInfo) != VK_SUCCESS) {
        throw ::std::runtime_error{ "failed to begin recording command buffer!\n" };
        return false;
    }

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = m_pSwapChain->getRenderPass();
    renderPassInfo.framebuffer = m_pSwapChain->getFrameBuffer(imageIndex);

    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent = m_pSwapChain->getSwapChainExtent();

    std::array<VkClearValue, 2> clearValues{};
    clearValues[0].color = {0.1f, 0.1f, 0.1f, 1.0f};
    clearValues[1].depthStencil = {1.0f, 0};
    renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    renderPassInfo.pClearValues = clearValues.data();

    vkCmdBeginRenderPass(m_commandBuffers[imageIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(m_pSwapChain->getSwapChainExtent().width);
    viewport.height = static_cast<float>(m_pSwapChain->getSwapChainExtent().height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    VkRect2D scissor{{0, 0}, m_pSwapChain->getSwapChainExtent()};
    vkCmdSetViewport(m_commandBuffers[imageIndex], 0, 1, &viewport);
    vkCmdSetScissor(m_commandBuffers[imageIndex], 0, 1, &scissor);

    m_pPipeline->bind(m_commandBuffers[imageIndex]);
    m_pModel->bind(m_commandBuffers[imageIndex]);
    m_pModel->draw(m_commandBuffers[imageIndex]);

    vkCmdEndRenderPass(m_commandBuffers[imageIndex]);
    if (vkEndCommandBuffer(m_commandBuffers[imageIndex]) != VK_SUCCESS) {
        throw ::std::runtime_error{ "Failed to record command buffer.\n" };
        return false;
    }
    return true;
}
