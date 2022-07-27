///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <AScene.hpp>
#include <Component/Control.hpp>
#include <Buffer.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::vksb::AScene::AScene()
    : m_uboBuffers{ ::vksb::SwapChain::MAX_FRAMES_IN_FLIGHT }
    , m_player{ m_registry.create() }
    , m_gameState{ *this }
{
    m_pDescriptorPool = ::vksb::descriptor::Pool::Builder{ m_device }
        .setMaxSets(::vksb::SwapChain::MAX_FRAMES_IN_FLIGHT)
        .addPoolSize(::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, ::vksb::SwapChain::MAX_FRAMES_IN_FLIGHT)
        .build();
    m_camera.setViewDirection(::glm::vec3{ 0.0f }, ::glm::vec3{ 0.0f, 0.0f, 1.0f });
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Rule of 5
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::vksb::AScene::~AScene() = default;



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Getters/Setters
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] auto ::vksb::AScene::getWindow()
    -> ::vksb::Window&
{
    return m_window;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Basic
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::AScene::run()
{
    for (auto& pUbo : m_uboBuffers) {
        pUbo = ::std::make_unique<::vksb::Buffer>(
            m_device,
            sizeof(AScene::Ubo),
            1,
            ::VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
            ::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
        );
        pUbo->map();
    }


    auto descriptorSetLayout{ ::vksb::descriptor::SetLayout::Builder{ m_device }
        .addBinding(0, ::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, ::VK_SHADER_STAGE_VERTEX_BIT)
        .build()
    };
    ::std::vector<::VkDescriptorSet> pDescriptorSets{ ::vksb::SwapChain::MAX_FRAMES_IN_FLIGHT };
    for (auto i{ 0uz }; i < pDescriptorSets.size(); ++i) {
        auto bufferInfo{ m_uboBuffers[i]->descriptorInfo() };
        ::vksb::descriptor::Writer{ *descriptorSetLayout, *m_pDescriptorPool }
            .writeBuffer(0, &bufferInfo)
            .build(pDescriptorSets[i]);
    }

    ::xrn::Clock m_clock;

    while (!m_window.shouldClose()) {
        m_gameState.deltaTime = m_clock.restart();

        m_window.handleEvents(*this);

        if (!this->onUpdate() || !this->update() || !this->postUpdate()) {
            m_window.close();
            break;
        }

        this->draw();
        this->limitFrameRate();
    }

    ::vkDeviceWaitIdle(m_device.device());
}

///////////////////////////////////////////////////////////////////////////
auto ::vksb::AScene::update()
    -> bool
{
    m_registry.view<::vksb::component::Transform3d, ::vksb::component::Control>().each(
        [this](auto& transform, auto& control){
            control.updatePosition(m_gameState.deltaTime, transform);
            control.updateRotation(transform);
        }
    );
    return true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::AScene::draw()
{
    const float aspect{ m_renderer.getAspectRatio() };
    // m_camera.setOrthographicProjection(-aspect, aspect, -1.0, 1.0, -1.0, 1.0);
    m_camera.setPerspectiveProjection(::glm::radians(50.0f), aspect, 0.1f, 10.0f);
    // m_camera.setViewTarget(
        // { 0.0f, 0.0f, 0.0f },
        // this->getPlayerComponent<::vksb::component::Transform3d>().getPosition()
    // );

    if ((m_gameState.commandBuffer = m_renderer.beginFrame())) {
        m_gameState.frameIndex = static_cast<::std::size_t>(m_renderer.getFrameIndex());
        m_gameState.projectionView = m_camera.getProjection() * m_camera.getView();

        // AScene::Ubo ubo{ .projectionView = m_camera.getProjection() * m_camera.getView() };
        // m_uboBuffers.writeToIndex(&ubo, m_gameState.frameIndex);
        // m_uboBuffers.flushIndex(m_gameState.frameIndex);

        m_renderer.beginSwapChainRenderPass(m_gameState.commandBuffer);
        m_registry.view<::vksb::component::Transform3d>().each([this](auto& transform){
            m_renderSystem(m_gameState, transform);
        });
        m_renderer.endSwapChainRenderPass(m_gameState.commandBuffer);
        m_renderer.endFrame();
    }
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::AScene::limitFrameRate()
{
    auto t{ ::xrn::Time::createAsSeconds(1) / m_maxFrameRate };
    if (t > m_gameState.deltaTime) {
        ::std::this_thread::sleep_for(::std::chrono::milliseconds(t - m_gameState.deltaTime));
    }
}
