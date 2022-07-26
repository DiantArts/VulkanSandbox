#pragma once

#include <Device.hpp>
#include <Descriptor/SetLayout.hpp>
#include <Descriptor/Pool.hpp>

namespace vksb::descriptor {

class Writer {
 public:
  Writer(::vksb::descriptor::SetLayout &setLayout, ::vksb::descriptor::Pool &pool);

  Writer &writeBuffer(::std::uint32_t binding, ::VkDescriptorBufferInfo *bufferInfo);
  Writer &writeImage(::std::uint32_t binding, ::VkDescriptorImageInfo *imageInfo);

  bool build(::VkDescriptorSet &set);
  void overwrite(::VkDescriptorSet &set);

 private:
  ::vksb::descriptor::SetLayout &setLayout;
  ::vksb::descriptor::Pool &pool;
  ::std::vector<::VkWriteDescriptorSet> writes;
};

}  // namespace vksb::descriptor
