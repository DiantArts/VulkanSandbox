#include <pch.hpp>
#include <Descriptor/Pool.hpp>

// *************** Descriptor Pool Builder *********************

::vksb::descriptor::Pool::Builder &::vksb::descriptor::Pool::Builder::addPoolSize(
    VkDescriptorType descriptorType, uint32_t count) {
  poolSizes.push_back({descriptorType, count});
  return *this;
}

::vksb::descriptor::Pool::Builder &::vksb::descriptor::Pool::Builder::setPoolFlags(
    VkDescriptorPoolCreateFlags flags) {
  poolFlags = flags;
  return *this;
}
::vksb::descriptor::Pool::Builder &::vksb::descriptor::Pool::Builder::setMaxSets(uint32_t count) {
  maxSets = count;
  return *this;
}

auto ::vksb::descriptor::Pool::Builder::build() const -> std::unique_ptr<::vksb::descriptor::Pool> {
  return std::make_unique<::vksb::descriptor::Pool>(device, maxSets, poolFlags, poolSizes);
}

// *************** Descriptor Pool *********************

::vksb::descriptor::Pool::Pool(
    ::vksb::Device &device,
    uint32_t maxSets,
    ::VkDescriptorPoolCreateFlags poolFlags,
    const ::std::vector<::VkDescriptorPoolSize> &poolSizes)
    : device{device} {
  ::VkDescriptorPoolCreateInfo descriptorPoolInfo{};
  descriptorPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  descriptorPoolInfo.poolSizeCount = static_cast<::std::uint32_t>(poolSizes.size());
  descriptorPoolInfo.pPoolSizes = poolSizes.data();
  descriptorPoolInfo.maxSets = maxSets;
  descriptorPoolInfo.flags = poolFlags;

  if (vkCreateDescriptorPool(device.device(), &descriptorPoolInfo, nullptr, &descriptorPool) !=
      VK_SUCCESS) {
      throw ::std::runtime_error("failed to create descriptor pool!");
  }
}

::vksb::descriptor::Pool::~Pool() {
  vkDestroyDescriptorPool(device.device(), descriptorPool, nullptr);
}

bool ::vksb::descriptor::Pool::allocateDescriptor(
    const ::VkDescriptorSetLayout descriptorSetLayout, ::VkDescriptorSet &descriptor) const {
  ::VkDescriptorSetAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  allocInfo.descriptorPool = descriptorPool;
  allocInfo.pSetLayouts = &descriptorSetLayout;
  allocInfo.descriptorSetCount = 1;

  // Might want to create a "DescriptorPoolManager" class that handles this case, and builds
  // a new pool whenever an old pool fills up. But this is beyond our current scope
  if (vkAllocateDescriptorSets(device.device(), &allocInfo, &descriptor) != VK_SUCCESS) {
    return false;
  }
  return true;
}

void ::vksb::descriptor::Pool::freeDescriptors(::std::vector<::VkDescriptorSet> &descriptors) const {
  vkFreeDescriptorSets(
      device.device(),
      descriptorPool,
      static_cast<::std::uint32_t>(descriptors.size()),
      descriptors.data());
}

void ::vksb::descriptor::Pool::resetPool() {
  vkResetDescriptorPool(device.device(), descriptorPool, 0);
}
