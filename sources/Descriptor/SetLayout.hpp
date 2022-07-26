#pragma once

#include <Device.hpp>

namespace vksb::descriptor {

class Writer;

class SetLayout {
 public:
  class Builder {
   public:
    Builder(::vksb::Device &device) : device{device} {}

    Builder &addBinding(
        ::std::uint32_t binding,
        ::VkDescriptorType descriptorType,
        ::VkShaderStageFlags stageFlags,
        ::std::uint32_t count = 1);
    ::std::unique_ptr<::vksb::descriptor::SetLayout> build() const;

   private:
    ::vksb::Device &device;
    ::std::unordered_map<::std::uint32_t, ::VkDescriptorSetLayoutBinding> bindings{};
  };

  SetLayout(
      ::vksb::Device &device, ::std::unordered_map<::std::uint32_t, ::VkDescriptorSetLayoutBinding> bindings);
  ~SetLayout();
  SetLayout(const ::vksb::descriptor::SetLayout &) = delete;
  SetLayout &operator=(const ::vksb::descriptor::SetLayout &) = delete;

  ::VkDescriptorSetLayout getDescriptorSetLayout() const { return descriptorSetLayout; }

 private:
  ::vksb::Device &device;
  ::VkDescriptorSetLayout descriptorSetLayout;
  ::std::unordered_map<::std::uint32_t, ::VkDescriptorSetLayoutBinding> bindings;

  friend class ::vksb::descriptor::Writer;
};

}  // namespace vksb
