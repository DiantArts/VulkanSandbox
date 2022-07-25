#pragma once

#include <Device.hpp>

namespace vksb {

class Buffer {
 public:
  Buffer(
      ::vksb::Device& device,
      VkDeviceSize instanceSize,
      uint32_t instanceCount,
      VkBufferUsageFlags usageFlags,
      VkMemoryPropertyFlags memoryPropertyFlags,
      VkDeviceSize minOffsetAlignment = 1);
  ~Buffer();

  Buffer(const Buffer&) = delete;
  Buffer& operator=(const Buffer&) = delete;

  VkResult map(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
  void unmap();

  void writeToBuffer(void* data, VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
  VkResult flush(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
  VkDescriptorBufferInfo descriptorInfo(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
  VkResult invalidate(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);

  void writeToIndex(void* data, int index);
  VkResult flushIndex(int index);
  VkDescriptorBufferInfo descriptorInfoForIndex(int index);
  VkResult invalidateIndex(int index);

  VkBuffer getBuffer() const { return buffer; }
  void* getMappedMemory() const { return mapped; }
  uint32_t getInstanceCount() const { return m_instanceCount; }
  VkDeviceSize getInstanceSize() const { return m_instanceSize; }
  VkDeviceSize getAlignmentSize() const { return m_instanceSize; }
  VkBufferUsageFlags getUsageFlags() const { return m_usageFlags; }
  VkMemoryPropertyFlags getMemoryPropertyFlags() const { return m_memoryPropertyFlags; }
  VkDeviceSize getBufferSize() const { return m_bufferSize; }

 private:
  static VkDeviceSize getAlignment(VkDeviceSize m_instanceSize, VkDeviceSize minOffsetAlignment);

  ::vksb::Device& device;
  void* mapped = nullptr;
  VkBuffer buffer = VK_NULL_HANDLE;
  VkDeviceMemory memory = VK_NULL_HANDLE;

  VkDeviceSize m_bufferSize;
  uint32_t m_instanceCount;
  VkDeviceSize m_instanceSize;
  VkDeviceSize m_alignmentSize;
  VkBufferUsageFlags m_usageFlags;
  VkMemoryPropertyFlags m_memoryPropertyFlags;
};

}  // namespace vksb
