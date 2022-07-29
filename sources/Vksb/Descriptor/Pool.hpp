#pragma once

#include <Vksb/Device.hpp>

namespace vksb::descriptor {

class Writer;

class Pool {
 public:
  class Builder {
   public:
    Builder(::vksb::Device &device) : device{device} {}

    Builder &addPoolSize(::VkDescriptorType descriptorType, ::std::uint32_t count);
    Builder &setPoolFlags(::VkDescriptorPoolCreateFlags flags);
    Builder &setMaxSets(::std::uint32_t count);
    ::std::unique_ptr<::vksb::descriptor::Pool> build() const;

   private:
    ::vksb::Device &device;
    ::std::vector<::VkDescriptorPoolSize> poolSizes{};
    ::std::uint32_t maxSets = 1000;
    ::VkDescriptorPoolCreateFlags poolFlags = 0;
  };

  Pool(
      ::vksb::Device &device,
      ::std::uint32_t maxSets,
      ::VkDescriptorPoolCreateFlags poolFlags,
      const ::std::vector<::VkDescriptorPoolSize> &poolSizes);
  ~Pool();
  Pool(const ::vksb::descriptor::Pool &) = delete;
  Pool &operator=(const ::vksb::descriptor::Pool &) = delete;

  bool allocateDescriptor(
      const ::VkDescriptorSetLayout descriptorSetLayout, ::VkDescriptorSet &descriptor) const;

  void freeDescriptors(std::vector<::VkDescriptorSet> &descriptors) const;

  void resetPool();

 private:
  ::vksb::Device &device;
  ::VkDescriptorPool descriptorPool;

  friend class ::vksb::descriptor::Writer;
};

}  // namespace vksb
