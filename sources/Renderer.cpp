///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Renderer.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::vksb::Renderer::Renderer(
    ::vksb::Window& window,
    ::vksb::Device& device
)
    : m_window{ window }
    , m_device{ device }
{
    this->recreateSwapChain();
    this->createCommandBuffers();
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Rule of 5
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::vksb::Renderer::~Renderer()
{
    this->freeCommandBuffers();
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Getters/setters
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////
auto ::vksb::Renderer::getSwapChainRenderPass() const
    -> ::VkRenderPass
{
    return m_pSwapChain->getRenderPass();
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////
auto ::vksb::Renderer::isFrameInProgress() const
    -> bool
{
    return m_isFrameStarted;
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////
auto ::vksb::Renderer::getCurrentCommandBuffer() const
    -> ::VkCommandBuffer
{
    assert(this->isFrameInProgress() && "Cannot get command buffer when frame is not in progress");
    return m_commandBuffers[m_currentFrameIndex];
}

///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] auto ::vksb::Renderer::getFrameIndex() const
    -> int
{
    assert(this->isFrameInProgress() && "Cannot get frame index when frame is not in progress");
    return m_currentFrameIndex;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Frame
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] auto ::vksb::Renderer::beginFrame()
    -> ::VkCommandBuffer
{
    assert(!this->isFrameInProgress() && "Cannot call beginFrame() while frame already in progress");
    switch (m_pSwapChain->acquireNextImage(&m_currentImageIndex)) {
    case VK_SUCCESS:
    case VK_SUBOPTIMAL_KHR:
        break;
    case VK_ERROR_OUT_OF_DATE_KHR:
        ::std::cout << "New swapchain needs to be created." << ::std::endl;
        m_window.setResizedFlag();
        this->recreateSwapChain();
        return nullptr;
    default:
        throw ::std::runtime_error{ "Failed to aquire swapChain image.\n" };
    }

    m_isFrameStarted = true;
    auto commandBuffer{ this->getCurrentCommandBuffer() };

    ::VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if (::vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
        throw ::std::runtime_error{ "Failed to begin recording command buffer!\n" };
    }
    return commandBuffer;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::Renderer::endFrame()
{
    assert(this->isFrameInProgress() && "Cannot call endFrame() if frame is not in progress");
    auto commandBuffer{ this->getCurrentCommandBuffer() };
    if (::vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
        throw ::std::runtime_error{ "Failed to record command buffer.\n" };
    }
    if (
        auto result{ m_pSwapChain->submitCommandBuffers(&commandBuffer, &m_currentImageIndex) };
        result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || m_window.wasResized()
    ) {
        m_window.resetResizedFlag();
        recreateSwapChain();
    } else if (result != VK_SUCCESS) {
        throw ::std::runtime_error{ "Failed to present swapChain image.\n" };
    }

    m_isFrameStarted = false;
    m_currentFrameIndex = (m_currentFrameIndex + 1) % ::vksb::SwapChain::MAX_FRAMES_IN_FLIGHT;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::Renderer::beginSwapChainRenderPass(
    ::VkCommandBuffer commandBuffer
)
{
    assert(this->isFrameInProgress() && "Cannot call beginSwapChainRenderPass() if frame is not in progress");
    assert(commandBuffer == getCurrentCommandBuffer() && "Cannot begin render pass on command buffer from a different frame");

    ::VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = m_pSwapChain->getRenderPass();
    renderPassInfo.framebuffer = m_pSwapChain->getFrameBuffer(m_currentImageIndex);

    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent = m_pSwapChain->getSwapChainExtent();

    std::array<::VkClearValue, 2> clearValues{};
    clearValues[0].color = {0.01f, 0.01f, 0.01f, 1.0f};
    clearValues[1].depthStencil = {1.0f, 0};
    renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    renderPassInfo.pClearValues = clearValues.data();

    ::vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    ::VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(m_pSwapChain->getSwapChainExtent().width);
    viewport.height = static_cast<float>(m_pSwapChain->getSwapChainExtent().height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    ::VkRect2D scissor{{0, 0}, m_pSwapChain->getSwapChainExtent()};
    ::vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
    ::vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::Renderer::endSwapChainRenderPass(
    ::VkCommandBuffer commandBuffer
)
{
    assert(this->isFrameInProgress() && "Cannot call endSwapChainRenderPass() if frame is not in progress");
    assert(commandBuffer == getCurrentCommandBuffer() && "Cannot end render pass on command buffer from a different frame");
    ::vkCmdEndRenderPass(commandBuffer);
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Helpers
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::Renderer::createCommandBuffers()
{
    m_commandBuffers.resize(::vksb::SwapChain::MAX_FRAMES_IN_FLIGHT);

    ::VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = m_device.getCommandPool();
    allocInfo.commandBufferCount = static_cast<uint32_t>(m_commandBuffers.size());

    if (vkAllocateCommandBuffers(m_device.device(), &allocInfo, m_commandBuffers.data()) != VK_SUCCESS) {
        throw ::std::runtime_error{ "Failed to allocate command buffers!\n" };
    }
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::Renderer::freeCommandBuffers()
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
void ::vksb::Renderer::recreateSwapChain()
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
        ::std::shared_ptr<::vksb::SwapChain> oldSwapchain{ ::std::move(m_pSwapChain) };
        m_pSwapChain = ::std::make_unique<::vksb::SwapChain>(m_device, windowSize, oldSwapchain);
        if (!oldSwapchain->compareSwapFormats(*m_pSwapChain.get())) {
            throw ::std::runtime_error{ "Swap chain image or depth format has changed" };
        }
    }
}
