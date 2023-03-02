///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Vksb/AScene.hpp>
#include <Vksb/Buffer.hpp>
#include <Vksb/Configuration.hpp>
#include <Vksb/Components.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::vksb::AScene::AScene()
    // create the vulkan things (I dont remember what it does)
    : m_pDescriptorSetLayout{ ::vksb::descriptor::SetLayout::Builder{ m_device }
        .addBinding(0, ::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, ::VK_SHADER_STAGE_ALL_GRAPHICS)
        .build()
    }
    // Keep track of information to help vulkan
    , m_frameInfo{ m_descriptorSets, *this }
    , m_uboBuffers{ ::vksb::SwapChain::MAX_FRAMES_IN_FLIGHT }
    , m_renderSystem{
        m_device,
        m_renderer.getSwapChainRenderPass(),
        m_pDescriptorSetLayout->getDescriptorSetLayout()
    }
    // draw lights and update their position
    , m_pointLightSystem{
        m_device,
        m_renderer.getSwapChainRenderPass(),
        m_pDescriptorSetLayout->getDescriptorSetLayout()
    }
    // entity that the player controls
    , m_player{ m_registry.create() }
    , m_camera{ m_registry.create() }
{
    // vulkan stuff
    m_pDescriptorPool = ::vksb::descriptor::Pool::Builder{ m_device }
        .setMaxSets(::vksb::SwapChain::MAX_FRAMES_IN_FLIGHT)
        .addPoolSize(::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, ::vksb::SwapChain::MAX_FRAMES_IN_FLIGHT)
        .build();

    for (auto& pUbo : m_uboBuffers) {
        pUbo = ::std::make_unique<::vksb::Buffer>(
            m_device,
            sizeof(::vksb::Ubo),
            1,
            ::VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
            ::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
        );
        pUbo->map();
    }

    for (auto i{ 0uz }; i < m_descriptorSets.size(); ++i) {
        auto bufferInfo{ m_uboBuffers[i]->descriptorInfo() };
        ::vksb::descriptor::Writer{ *m_pDescriptorSetLayout, *m_pDescriptorPool }
            .writeBuffer(0, &bufferInfo)
            .build(m_descriptorSets[i]);
    }

    // hardcode cube as player
    m_registry.emplace<::vksb::component::Control>(m_player); // player always is controllable

    m_registry.emplace<::vksb::component::Control>(m_camera.getId());
    m_registry.emplace<::vksb::component::Position>(m_camera.getId(), ::glm::vec3{ 0.0f, 0.0f, -2.5f });
    m_registry.emplace<::vksb::component::Rotation>(m_camera.getId(), ::glm::vec3{ 90.0f, 0.0f, 0.0f });
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
    ::xrn::Clock m_clock;

    while (!m_window.shouldClose()) {
        m_frameInfo.deltaTime = m_clock.restart();

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
    this->updateCamera();

    // control
    for (auto [entity, control]: m_registry.view<::vksb::component::Control>().each()) {
        auto* pPosition{ m_registry.try_get<::vksb::component::Position>(entity) };
        auto* pRotation{ m_registry.try_get<::vksb::component::Rotation>(entity) };

        if (pRotation) {
            if (control.isRotated()) {
                pRotation->updateDirection(control.getRotation());
                control.resetRotatedFlag();
            }
            if (pPosition) {
                pPosition->update(m_frameInfo.deltaTime, control, pRotation->getDirection());
            }
        } else {
            if (pPosition) {
                auto direction{
                    ::glm::normalize(::glm::vec3(
                        cos(::glm::radians(0.0f)) * cos(::glm::radians(0.0f)),
                        sin(::glm::radians(0.0f)),
                        sin(::glm::radians(0.0f)) * cos(::glm::radians(0.0f))
                    ))
                };
                pPosition->update(m_frameInfo.deltaTime, control, direction);
            }
        }
    }

    // transform (apply position rotation scale)
    for (auto [entity, transform]: m_registry.view<::vksb::component::Transform3d>().each()) {
        auto* pPosition{ m_registry.try_get<::vksb::component::Position>(entity) };
        auto* pRotation{ m_registry.try_get<::vksb::component::Rotation>(entity) };
        auto* pScale{ m_registry.try_get<::vksb::component::Scale>(entity) };

        // matrix and normalMatrix
        if (pPosition) {
            if (pRotation) {
                if (pScale) {
                    if (pPosition->isChanged() || pRotation->isChanged() || pScale->isChanged()) {
                        transform.updateMatrix(*pPosition, *pRotation, *pScale);
                        transform.updateNormalMatrix(*pRotation, *pScale);
                    }
                    pScale->resetChangedFlag();
                    pRotation->resetChangedFlag();
                } else if (pPosition->isChanged() || pRotation->isChanged()) {
                    transform.updateMatrix(*pPosition, *pRotation);
                    transform.updateNormalMatrix(*pRotation);
                    pRotation->resetChangedFlag();
                }
            } else {
                if (pScale) {
                    if (pPosition->isChanged() || pScale->isChanged()) {
                        transform.updateMatrix(*pPosition);
                        transform.updateMatrix(*pPosition, { 0.0f, 0.0f, 0.0f }, *pScale);
                        transform.updateNormalMatrix(*pScale);
                        pScale->resetChangedFlag();
                    }
                } else if (pPosition->isChanged()) {
                    transform.updateMatrix(*pPosition);
                }
            }
            pPosition->resetChangedFlag();
        }
    }

    {
        auto lightIndex{ 0uz };
        m_registry.view<::vksb::component::PointLight, ::vksb::component::Position>().each(
            [this, &lightIndex](auto& pointLight, auto& position) {
                m_pointLightSystem.update(m_frameInfo, pointLight, position, lightIndex);
                ++lightIndex;
            }
        );
        m_frameInfo.ubo.numOfLights = lightIndex;
    }

    {
        auto& position{ m_registry.get<::vksb::component::Position>(m_camera.getId()) };
        auto& rotation{ m_registry.get<::vksb::component::Rotation>(m_camera.getId()) };
        m_camera.setViewDirection(position, rotation.getDirection());
        // m_camera.setViewDirection(::glm::vec3{ 0.0f, 0.0f, -2.5f }, ::glm::vec3{ 0.0f, 0.0f, 1.0f });
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::AScene::updateCamera()
{
    const float aspect{ m_renderer.getAspectRatio() };
    // m_camera.setOrthographicProjection(-aspect, aspect, -1.0, 1.0, -1.0, 1.0);
    m_camera.setPerspectiveProjection(::glm::radians(50.0f), aspect, 0.1f, 1000.0f);
    // m_camera.setViewTarget(
        // { 0.0f, 0.0f, 0.0f },
        // this->getPlayerComponent<::vksb::component::Transform3d>().getPosition()
    // );

    m_frameInfo.projectionView = m_camera.getProjection() * m_camera.getView();
    m_frameInfo.ubo.projection = m_camera.getProjection();
    m_frameInfo.ubo.view= m_camera.getView();
}


///////////////////////////////////////////////////////////////////////////
void ::vksb::AScene::draw()
{

    if (!(m_frameInfo.commandBuffer = m_renderer.beginFrame())) {
        return;
    }
    m_frameInfo.frameIndex = static_cast<::std::size_t>(m_renderer.getFrameIndex());

    m_uboBuffers[m_frameInfo.frameIndex]->writeToBuffer(&m_frameInfo.ubo);
    m_uboBuffers[m_frameInfo.frameIndex]->flush();

    m_renderer.beginSwapChainRenderPass(m_frameInfo.commandBuffer);

    m_renderSystem.bind(m_frameInfo);
    m_registry.view<::vksb::component::Transform3d>().each([this](auto& transform){
        m_renderSystem(m_frameInfo, transform);
    });

    m_pointLightSystem.bind(m_frameInfo);
    m_registry.view<::vksb::component::PointLight, ::vksb::component::Position>().each(
        [this](auto& pointLight, auto position) { m_pointLightSystem(m_frameInfo, pointLight, position); }
    );

    m_renderer.endSwapChainRenderPass(m_frameInfo.commandBuffer);
    m_renderer.endFrame();
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::AScene::limitFrameRate()
{
    auto t{ ::xrn::Time::createAsSeconds(1) / ::vksb::configuration.maxFrameRate };
    if (t > m_frameInfo.deltaTime) {
        ::std::this_thread::sleep_for(::std::chrono::milliseconds(t - m_frameInfo.deltaTime));
    }
}
