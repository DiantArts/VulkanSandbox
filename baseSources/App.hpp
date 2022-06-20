#pragma once

#include <Device.hpp>
#include <Pipeline.hpp>
#include <SwapChain.hpp>
#include <Window.hpp>

// std
#include <memory>
#include <vector>

namespace xrn {
class FirstApp {
 public:
  static constexpr int WIDTH = 800;
  static constexpr int HEIGHT = 600;

  FirstApp();
  ~FirstApp();

  FirstApp(const FirstApp &) = delete;
  FirstApp &operator=(const FirstApp &) = delete;

  void run();

 private:
  void createPipelineLayout();
  void createPipeline();
  void createCommandBuffers();
  void drawFrame();

  Window lveWindow{WIDTH, HEIGHT, "Hello Vulkan!"};
  Device lveDevice{lveWindow};
  SwapChain lveSwapChain{lveDevice, lveWindow.getExtent()};
  std::unique_ptr<Pipeline> lvePipeline;
  VkPipelineLayout pipelineLayout;
  std::vector<VkCommandBuffer> commandBuffers;
};
}  // namespace xrn
