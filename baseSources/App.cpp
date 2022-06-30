#include <pch.hpp>
#include <App.hpp>

// std
#include <array>
#include <cassert>
#include <stdexcept>

namespace vksb {

App::App() {
  loadModels();
  createPipelineLayout();
  recreateSwapChain();
  createCommandBuffers();
}

App::~App() { vkDestroyPipelineLayout(m_device.device(), m_pipelineLayout, nullptr); }

::std::uint8_t App::run() {
  while (!m_window.shouldClose()) {
    glfwPollEvents();
    drawFrame();
  }

  vkDeviceWaitIdle(m_device.device());
  return 0;
}

void App::loadModels() {
  std::vector<Model::Vertex> vertices{
      {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
      {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
      {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}};
  m_pModel = std::make_unique<Model>(m_device, vertices);
}

void App::createPipelineLayout() {
  VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
  pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipelineLayoutInfo.setLayoutCount = 0;
  pipelineLayoutInfo.pSetLayouts = nullptr;
  pipelineLayoutInfo.pushConstantRangeCount = 0;
  pipelineLayoutInfo.pPushConstantRanges = nullptr;
  if (vkCreatePipelineLayout(m_device.device(), &pipelineLayoutInfo, nullptr, &m_pipelineLayout) !=
      VK_SUCCESS) {
    throw std::runtime_error("failed to create pipeline layout!");
  }
}

void App::recreateSwapChain() {
  auto extent = m_window.getSize();
  while (extent.width == 0 || extent.height == 0) {
    extent = m_window.getSize();
    glfwWaitEvents();
  }
  vkDeviceWaitIdle(m_device.device());

  if (m_pSwapChain == nullptr) {
    m_pSwapChain = std::make_unique<SwapChain>(m_device, extent);
  } else {
    m_pSwapChain = std::make_unique<SwapChain>(m_device, extent, std::move(m_pSwapChain));
    if (m_pSwapChain->imageCount() != m_commandBuffers.size()) {
      freeCommandBuffers();
      createCommandBuffers();
    }
  }

  createPipeline();
}

void App::createPipeline() {
  assert(m_pSwapChain != nullptr && "Cannot create pipeline before swap chain");
  assert(m_pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");

  ::vksb::Pipeline::Configuration pipelineConfig{};
  pipelineConfig.renderPass = m_pSwapChain->getRenderPass();
  pipelineConfig.pipelineLayout = m_pipelineLayout;
  m_pPipeline = std::make_unique<Pipeline>(
      m_device,
      pipelineConfig,
      "simple");
}

void App::createCommandBuffers() {
  m_commandBuffers.resize(m_pSwapChain->imageCount());

  VkCommandBufferAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandPool = m_device.getCommandPool();
  allocInfo.commandBufferCount = static_cast<uint32_t>(m_commandBuffers.size());

  if (vkAllocateCommandBuffers(m_device.device(), &allocInfo, m_commandBuffers.data()) !=
      VK_SUCCESS) {
    throw std::runtime_error("failed to allocate command buffers!");
  }
}

void App::freeCommandBuffers() {
  vkFreeCommandBuffers(
      m_device.device(),
      m_device.getCommandPool(),
      static_cast<uint32_t>(m_commandBuffers.size()),
      m_commandBuffers.data());
  m_commandBuffers.clear();
}

void App::recordCommandBuffer(::std::size_t imageIndex) {
  VkCommandBufferBeginInfo beginInfo{};
  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

  if (vkBeginCommandBuffer(m_commandBuffers[imageIndex], &beginInfo) != VK_SUCCESS) {
    throw std::runtime_error("failed to begin recording command buffer!");
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
    throw std::runtime_error("failed to record command buffer!");
  }
}

void App::drawFrame() {
  uint32_t imageIndex;
  auto result = m_pSwapChain->acquireNextImage(&imageIndex);

  if (result == VK_ERROR_OUT_OF_DATE_KHR) {
    recreateSwapChain();
    return;
  }

  if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
    throw std::runtime_error("failed to acquire swap chain image!");
  }

  recordCommandBuffer(imageIndex);
  result = m_pSwapChain->submitCommandBuffers(&m_commandBuffers[imageIndex], &imageIndex);
  if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR ||
      m_window.wasResized()) {
    m_window.setResizedFlag();
    recreateSwapChain();
    return;
  } else if (result != VK_SUCCESS) {
    throw std::runtime_error("failed to present swap chain image!");
  }
}

}  // namespace vksb
