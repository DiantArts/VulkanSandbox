///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Pipeline.hpp>
#include <Window.hpp>
#include <Device.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// static elements
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::vksb::Pipeline::Configuration::Configuration(
    ::std::size_t width,
    ::std::size_t height
)
{
    this->inputAssemblyInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    this->inputAssemblyInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    this->inputAssemblyInfo.primitiveRestartEnable = VK_FALSE;

    this->viewport.x = 0.0f;
    this->viewport.y = 0.0f;
    this->viewport.width = static_cast<float>(width);
    this->viewport.height = static_cast<float>(height);
    this->viewport.minDepth = 0.0f;
    this->viewport.maxDepth = 1.0f;

    this->scissor.offset = { 0, 0 };
    this->scissor.extent = { width, height };

    this->rasterizationInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    this->rasterizationInfo.depthClampEnable = VK_FALSE;
    this->rasterizationInfo.rasterizerDiscardEnable = VK_FALSE;
    this->rasterizationInfo.polygonMode = VK_POLYGON_MODE_FILL;
    this->rasterizationInfo.lineWidth = 1.0f;
    this->rasterizationInfo.cullMode = VK_CULL_MODE_NONE;
    this->rasterizationInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
    this->rasterizationInfo.depthBiasEnable = VK_FALSE;
    this->rasterizationInfo.depthBiasConstantFactor = 0.0f;  // Optional
    this->rasterizationInfo.depthBiasClamp = 0.0f;           // Optional
    this->rasterizationInfo.depthBiasSlopeFactor = 0.0f;     // Optional

    this->multisampleInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    this->multisampleInfo.sampleShadingEnable = VK_FALSE;
    this->multisampleInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    this->multisampleInfo.minSampleShading = 1.0f;           // Optional
    this->multisampleInfo.pSampleMask = nullptr;             // Optional
    this->multisampleInfo.alphaToCoverageEnable = VK_FALSE;  // Optional
    this->multisampleInfo.alphaToOneEnable = VK_FALSE;       // Optional

    this->colorBlendAttachment.colorWriteMask =
        VK_COLOR_COMPONENT_R_BIT |
        VK_COLOR_COMPONENT_G_BIT |
        VK_COLOR_COMPONENT_B_BIT |
        VK_COLOR_COMPONENT_A_BIT;
    this->colorBlendAttachment.blendEnable = VK_FALSE;
    this->colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;   // Optional
    this->colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;  // Optional
    this->colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;              // Optional
    this->colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;   // Optional
    this->colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;  // Optional
    this->colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;              // Optional

    this->colorBlendInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    this->colorBlendInfo.logicOpEnable = VK_FALSE;
    this->colorBlendInfo.logicOp = VK_LOGIC_OP_COPY;  // Optional
    this->colorBlendInfo.attachmentCount = 1;
    this->colorBlendInfo.pAttachments = &this->colorBlendAttachment;
    this->colorBlendInfo.blendConstants[0] = 0.0f;  // Optional
    this->colorBlendInfo.blendConstants[1] = 0.0f;  // Optional
    this->colorBlendInfo.blendConstants[2] = 0.0f;  // Optional
    this->colorBlendInfo.blendConstants[3] = 0.0f;  // Optional

    this->depthStencilInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    this->depthStencilInfo.depthTestEnable = VK_TRUE;
    this->depthStencilInfo.depthWriteEnable = VK_TRUE;
    this->depthStencilInfo.depthCompareOp = VK_COMPARE_OP_LESS;
    this->depthStencilInfo.depthBoundsTestEnable = VK_FALSE;
    this->depthStencilInfo.minDepthBounds = 0.0f;  // Optional
    this->depthStencilInfo.maxDepthBounds = 1.0f;  // Optional
    this->depthStencilInfo.stencilTestEnable = VK_FALSE;
    this->depthStencilInfo.front = {};  // Optional
    this->depthStencilInfo.back = {};   // Optional
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::vksb::Pipeline::Pipeline(
    ::vksb::Device& device,
    const Pipeline::Configuration& configuration,
    const ::std::string_view shaderFilenames
)
    : m_device{ device }
{
    assert(
        configuration.pipelineLayout != VK_NULL_HANDLE &&
        "Cannot create graphics pipeline: no pipelineLayout provided in the configuration"
    );
    assert(
        configuration.renderPass != VK_NULL_HANDLE &&
        "Cannot create graphics pipeline: no renderPass provided in the configuration");


    ::std::string filepath;

    // Vertex file
    filepath.reserve(
        Pipeline::shadersDirectory.size() + Pipeline::vertexDirectory.size() +
        shaderFilenames.size() + Pipeline::vertexExtension.size()
    );
    filepath = Pipeline::shadersDirectory;
    filepath += Pipeline::vertexDirectory;
    filepath += shaderFilenames;
    filepath += Pipeline::vertexExtension;
    if (!this->createShaderModule(filepath, m_vertexShaderModule)) {
        return;
    }

    // Fragment file
    filepath.reserve(
        Pipeline::shadersDirectory.size() + Pipeline::fragmentDirectory.size() +
        shaderFilenames.size() + Pipeline::fragmentExtension.size()
    );
    filepath = Pipeline::shadersDirectory;
    filepath += Pipeline::fragmentDirectory;
    filepath += shaderFilenames;
    filepath += Pipeline::fragmentExtension;
    if (!this->createShaderModule(filepath, m_fragmentShaderModule)) {
        return;
    }

    ::VkPipelineShaderStageCreateInfo shaderStages[2];
    shaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
    shaderStages[0].module = m_vertexShaderModule;
    shaderStages[0].pName = "main";
    shaderStages[0].flags = 0;
    shaderStages[0].pNext = nullptr;
    shaderStages[0].pSpecializationInfo = nullptr;
    shaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    shaderStages[1].module = m_fragmentShaderModule;
    shaderStages[1].pName = "main";
    shaderStages[1].flags = 0;
    shaderStages[1].pNext = nullptr;
    shaderStages[1].pSpecializationInfo = nullptr;

    ::VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexAttributeDescriptionCount = 0;
    vertexInputInfo.pVertexAttributeDescriptions = nullptr;
    vertexInputInfo.vertexBindingDescriptionCount = 0;
    vertexInputInfo.pVertexBindingDescriptions = nullptr;

    ::VkPipelineViewportStateCreateInfo viewportInfo{};
    viewportInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportInfo.viewportCount = 1;
    viewportInfo.pViewports = &configuration.viewport;
    viewportInfo.scissorCount = 1;
    viewportInfo.pScissors = &configuration.scissor;

    ::VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = shaderStages;
    pipelineInfo.pVertexInputState = &vertexInputInfo;
    pipelineInfo.pInputAssemblyState = &configuration.inputAssemblyInfo;
    pipelineInfo.pViewportState = &viewportInfo;
    pipelineInfo.pRasterizationState = &configuration.rasterizationInfo;
    pipelineInfo.pMultisampleState = &configuration.multisampleInfo;
    pipelineInfo.pColorBlendState = &configuration.colorBlendInfo;
    pipelineInfo.pDepthStencilState = &configuration.depthStencilInfo;
    pipelineInfo.pDynamicState = nullptr;

    pipelineInfo.layout = configuration.pipelineLayout;
    pipelineInfo.renderPass = configuration.renderPass;
    pipelineInfo.subpass = configuration.subpass;

    pipelineInfo.basePipelineIndex = -1;
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

    if (
        ::vkCreateGraphicsPipelines(
            m_device.device(),
            VK_NULL_HANDLE,
            1,
            &pipelineInfo,
            nullptr,
            &m_graphicsPipeline
        ) != VK_SUCCESS
    ) {
        ::xrn::Logger::openError() << "failed to create pipeline.\n";
    }
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Rule of 5
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/// \brief Destructor
///
///////////////////////////////////////////////////////////////////////////
::vksb::Pipeline::~Pipeline()
{
    ::vkDestroyShaderModule(m_device.device(), m_vertexShaderModule, nullptr);
    ::vkDestroyShaderModule(m_device.device(), m_fragmentShaderModule, nullptr);
    ::vkDestroyPipeline(m_device.device(), m_graphicsPipeline, nullptr);
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Vulkan stuff
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::Pipeline::bind(
    ::VkCommandBuffer commandBuffer
)
{
    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_graphicsPipeline);
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Getters
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] auto ::vksb::Pipeline::getDevice()
    -> ::vksb::Device&
{
    return m_device;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Helpers
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
auto ::vksb::Pipeline::createShaderModule(
    const ::std::string& filepath,
    ::VkShaderModule& shaderModule
) -> bool
{
    // open the file
    ::std::ifstream file{ filepath, ::std::ios::ate | ::std::ios::binary };
    if (!file.is_open()) {
        ::xrn::Logger::openError() << "File '" << filepath << "' has failed to open.\n";
        return false;
    }

    // check its size
    ::std::size_t fileSize{ static_cast<::std::size_t>(file.tellg()) };

    // get its content
    ::std::vector<::std::byte> code;
    code.resize(fileSize);
    file.seekg(0);
    file.read(::std::bit_cast<char*>(code.data()), fileSize);

    // create info shader module
    ::VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = ::std::bit_cast<const ::std::uint32_t*>(code.data());

    // create the shader module
    if (::vkCreateShaderModule(m_device.device(), &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
        ::xrn::Logger::openError() << "Failed to create Vulkan shader module.\n";
        return false;
    }

    return true;
}
