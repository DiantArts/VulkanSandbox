///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// extern
///////////////////////////////////////////////////////////////////////////
#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tiny_obj_loader.h>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Vksb/Model.hpp>
#include <Vksb/Configuration.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Hash specialization
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

namespace std {

template <>
struct hash<::vksb::Model::Vertex> {
    auto operator()(
        ::vksb::Model::Vertex const &vertex
    ) const
      -> ::std::size_t
    {
        auto seed{ 0uz };
        ::vksb::hashCombine(seed, vertex.position, vertex.color, vertex.normal, vertex.uv);
        return seed;
    }
};

}  // namespace std



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Static
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
auto ::vksb::Model::Vertex::getBindingDescriptions()
    -> ::std::vector<::VkVertexInputBindingDescription>
{
    return { {
        .binding = 0,
        .stride = sizeof(::vksb::Model::Vertex),
        .inputRate = VK_VERTEX_INPUT_RATE_VERTEX
    } };
}

///////////////////////////////////////////////////////////////////////////
auto ::vksb::Model::Vertex::getAttributeDescriptions()
    -> ::std::vector<::VkVertexInputAttributeDescription>
{
    return { {
        .location = 0,
        .binding = 0,
        .format = VK_FORMAT_R32G32B32_SFLOAT,
        .offset = offsetof(::vksb::Model::Vertex, Vertex::position)
    }, {
        .location = 1,
        .binding = 0,
        .format = VK_FORMAT_R32G32B32_SFLOAT,
        .offset = offsetof(::vksb::Model::Vertex, Vertex::color)
    }, {
        .location = 2,
        .binding = 0,
        .format = VK_FORMAT_R32G32B32_SFLOAT,
        .offset = offsetof(::vksb::Model::Vertex, Vertex::normal)
    }, {
        .location = 3,
        .binding = 0,
        .format = VK_FORMAT_R32G32B32_SFLOAT,
        .offset = offsetof(::vksb::Model::Vertex, Vertex::uv)
    } };
}

///////////////////////////////////////////////////////////////////////////
auto ::vksb::Model::Vertex::operator==(
    const Vertex &other
) const
    -> bool
{
  return this->position == other.position && this->color == other.color && this->normal == other.normal &&
      uv == other.uv;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::Model::Builder::loadFromFile(
    ::std::string_view filename
)
{
    ::tinyobj::attrib_t attrib;
    ::std::vector<::tinyobj::shape_t> shapes;
    ::std::vector<::tinyobj::material_t> materials;
    ::std::string warning, error;

    ::std::string filepath;
    filepath.reserve(
        ::vksb::configuration.filepath.modelDirectory.size() + filename.size() +
        ::vksb::configuration.filepath.modelExtension.size()
    );
    filepath = ::vksb::configuration.filepath.modelDirectory;
    filepath += filename;
    filepath += ::vksb::configuration.filepath.modelExtension;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warning, &error, filepath.c_str())) {
        throw ::std::runtime_error(warning + error);
    }

    vertices.clear();
    indices.clear();

    ::std::unordered_map<::vksb::Model::Vertex, ::std::size_t> uniqueVertices{};
    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            ::vksb::Model::Vertex vertex{};

            if (index.vertex_index >= 0) {
                vertex.position = {
                    attrib.vertices[3 * index.vertex_index + 0],
                    attrib.vertices[3 * index.vertex_index + 1],
                    attrib.vertices[3 * index.vertex_index + 2]
                };
            }

            vertex.color = {
                attrib.colors[3 * index.vertex_index + 0],
                attrib.colors[3 * index.vertex_index + 1],
                attrib.colors[3 * index.vertex_index + 2]
            };

            if (index.normal_index >= 0) {
                vertex.normal = {
                    attrib.normals[3 * index.normal_index + 0],
                    attrib.normals[3 * index.normal_index + 1],
                    attrib.normals[3 * index.normal_index + 2]
                };
            }

            if (index.texcoord_index >= 0) {
                vertex.uv = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    attrib.texcoords[2 * index.texcoord_index + 1]
                };
            }

            if (!uniqueVertices.count(vertex)) {
                uniqueVertices[vertex] = static_cast<::std::size_t>(vertices.size());
                vertices.push_back(::std::move(vertex));
            }
            indices.push_back(uniqueVertices[vertex]);
        }
    }
}

///////////////////////////////////////////////////////////////////////////
auto ::vksb::Model::createFromFile(
    ::vksb::Device& device,
    ::std::string_view filename
) -> ::std::unique_ptr<::vksb::Model>
{
    Model::Builder modelBuilder;
    modelBuilder.loadFromFile(filename);
    return ::std::make_unique<::vksb::Model>(device, modelBuilder);
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::vksb::Model::Model(
    ::vksb::Device& device,
    const Model::Builder& builder
)
    : m_device{ device }
{
    this->createVertexBuffers(builder.vertices);
    this->createIndexBuffers(builder.indices);
}




///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Rule of 5
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::vksb::Model::~Model() = default;


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Basic
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::Model::bind(
    ::VkCommandBuffer commandBuffer
)
{
    ::VkBuffer buffers[] = { m_vertexBuffer->getBuffer() };
    ::VkDeviceSize offsets[] = { 0 };
    ::vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);

    if (m_hasIndexBuffer) {
        ::vkCmdBindIndexBuffer(commandBuffer, m_indexBuffer->getBuffer(), 0, VK_INDEX_TYPE_UINT32);
    }
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::Model::draw(
    ::VkCommandBuffer commandBuffer
)
{
    if (m_hasIndexBuffer) {
        ::vkCmdDrawIndexed(commandBuffer, m_indexCount, 1, 0, 0, 0);
    } else {
        ::vkCmdDraw(commandBuffer, m_vertexCount, 1, 0, 0);
    }
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Helpers
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::Model::createVertexBuffers(
    const ::std::vector<Model::Vertex>& vertices
)
{
    m_vertexCount = static_cast<::std::uint32_t>(vertices.size());
    if (m_vertexCount < 3) {
        throw ::std::runtime_error{ "Vertex count must be at least 3" };
    }
    ::std::size_t vertexSize{ sizeof(vertices[0]) };
    ::VkDeviceSize bufferSize{ vertexSize * m_vertexCount };

    ::vksb::Buffer stagingBuffer{
        m_device,
        vertexSize,
        m_vertexCount,
        ::VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        ::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | ::VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
    };
    stagingBuffer.map();
    stagingBuffer.writeToBuffer(::std::bit_cast<void*>(vertices.data()));

    m_vertexBuffer = ::std::make_unique<::vksb::Buffer>(
        m_device,
        vertexSize,
        m_vertexCount,
        ::VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | ::VK_BUFFER_USAGE_TRANSFER_DST_BIT,
        ::VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
    );
    m_device.copyBuffer(stagingBuffer.getBuffer(), m_vertexBuffer->getBuffer(), bufferSize);
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::Model::createIndexBuffers(
    const ::std::vector<::std::uint32_t>& indices
)
{
    m_indexCount = static_cast<::std::uint32_t>(indices.size());
    if (!(m_hasIndexBuffer = m_indexCount > 0)) {
        return;
    }
    ::std::size_t indexSize{ sizeof(indices[0]) };
    ::VkDeviceSize bufferSize{ indexSize * m_indexCount };

    ::vksb::Buffer stagingBuffer{
        m_device,
        indexSize,
        m_indexCount,
        ::VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        ::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | ::VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
    };
    stagingBuffer.map();
    stagingBuffer.writeToBuffer(::std::bit_cast<void*>(indices.data()));

    m_indexBuffer = ::std::make_unique<::vksb::Buffer>(
        m_device,
        indexSize,
        m_indexCount,
        ::VK_BUFFER_USAGE_INDEX_BUFFER_BIT | ::VK_BUFFER_USAGE_TRANSFER_DST_BIT,
        ::VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
    );
    m_device.copyBuffer(stagingBuffer.getBuffer(), m_indexBuffer->getBuffer(), bufferSize);
}
