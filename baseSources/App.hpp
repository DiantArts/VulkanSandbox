#pragma once

#include <Device.hpp>
#include <Model.hpp>
#include <Pipeline.hpp>
#include <SwapChain.hpp>
#include <Window.hpp>

// std
#include <memory>
#include <vector>

namespace vksb {
class App {
 public:
  static constexpr int WIDTH = 800;
  static constexpr int HEIGHT = 600;

  App();
  ~App();

  App(const App &) = delete;
  App &operator=(const App &) = delete;

  ::std::uint8_t run();

 private:
  void loadModels();
  void createPipelineLayout();
  void createPipeline();
  void createCommandBuffers();
  void freeCommandBuffers();
  void drawFrame();
  void recreateSwapChain();
  void recordCommandBuffer(int imageIndex);

  Window m_window{WIDTH, HEIGHT, "Vulkan Tutorial"};
  Device m_device{m_window};
  std::unique_ptr<SwapChain> m_pSwapChain;
  std::unique_ptr<Pipeline> m_pPipeline;
  VkPipelineLayout pipelineLayout;
  std::vector<VkCommandBuffer> commandBuffers;
  std::unique_ptr<Model> m_pModel;
};
}  // namespace vksb
