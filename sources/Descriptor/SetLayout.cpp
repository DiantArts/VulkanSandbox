#include <pch.hpp>
#include <Descriptor/SetLayout.hpp>

// *************** Descriptor Set Layout Builder *********************

::vksb::descriptor::SetLayout::Builder &::vksb::descriptor::SetLayout::Builder::addBinding(
    ::std::uint32_t binding,
    ::VkDescriptorType descriptorType,
    ::VkShaderStageFlags stageFlags,
    ::std::uint32_t count) {
  assert(bindings.count(binding) == 0 && "Binding already in use");
  ::VkDescriptorSetLayoutBinding layoutBinding{};
  layoutBinding.binding = binding;
  layoutBinding.descriptorType = descriptorType;
  layoutBinding.descriptorCount = count;
  layoutBinding.stageFlags = stageFlags;
  bindings[binding] = layoutBinding;
  return *this;
}

auto ::vksb::descriptor::SetLayout::Builder::build() const -> ::std::unique_ptr<::vksb::descriptor::SetLayout> {
    return ::std::make_unique<::vksb::descriptor::SetLayout>(device, bindings);
}

// *************** Descriptor Set Layout *********************

::vksb::descriptor::SetLayout::SetLayout(
    ::vksb::Device &device, ::std::unordered_map<::std::uint32_t, ::VkDescriptorSetLayoutBinding> bindings)
    : device{device}, bindings{bindings} {
  ::std::vector<::VkDescriptorSetLayoutBinding> setLayoutBindings{};
  for (auto kv : bindings) {
    setLayoutBindings.push_back(kv.second);
  }

  ::VkDescriptorSetLayoutCreateInfo descriptorSetLayoutInfo{};
  descriptorSetLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  descriptorSetLayoutInfo.bindingCount = static_cast<::std::uint32_t>(setLayoutBindings.size());
  descriptorSetLayoutInfo.pBindings = setLayoutBindings.data();

  if (vkCreateDescriptorSetLayout(
          device.device(),
          &descriptorSetLayoutInfo,
          nullptr,
          &descriptorSetLayout) != VK_SUCCESS) {
      throw ::std::runtime_error("failed to create descriptor set layout!");
  }
}

::vksb::descriptor::SetLayout::~SetLayout() {
  vkDestroyDescriptorSetLayout(device.device(), descriptorSetLayout, nullptr);
}
