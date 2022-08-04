#pragma once

#include <Vksb/Device.hpp>
#include <Vksb/Pipeline.hpp>
#include <Vksb/FrameInfo.hpp>

namespace vksb::system {
class PointLight {
 public:
  PointLight(
      ::vksb::Device &device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);
  ~PointLight();

  PointLight(const PointLight &) = delete;
  PointLight &operator=(const PointLight &) = delete;

  void bind(vksb::FrameInfo& frameInfo);
  void operator()(vksb::FrameInfo &frameInfo);

 private:
  void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
  void createPipeline(VkRenderPass renderPass);

  ::vksb::Device &lveDevice;

  std::unique_ptr<::vksb::Pipeline> lvePipeline;
  VkPipelineLayout pipelineLayout;
};
}  // namespace vksb::system
