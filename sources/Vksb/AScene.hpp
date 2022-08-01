#pragma once

#include <xrn/Util.hpp>
#include <Vksb/Window.hpp>
#include <Vksb/Device.hpp>
#include <Vksb/Renderer.hpp>
#include <Vksb/FrameInfo.hpp>
#include <Vksb/System/Render.hpp>
#include <Vksb/System/PointLight.hpp>
#include <Vksb/Camera.hpp>
#include <Vksb/Descriptor.hpp>

namespace vksb {

///////////////////////////////////////////////////////////////////////////
/// \brief No clue what it does xD
/// \ingroup vulkan
///
/// \include AScene.hpp <AScene.hpp>
///
///////////////////////////////////////////////////////////////////////////
class AScene {

public:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Static
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    struct Ubo {
        ::glm::mat4 projection{ 1.0f };
        ::glm::mat4 view{ 1.0f };
        ::glm::vec4 ambientLightColor{ 1.0f, 1.0f, 1.0f, 0.02f }; // w is intensity

        // ::glm::vec3 lightDirection{ ::glm::normalize(::glm::vec3{ 1.0f, -3.0f, -1.0f }) };
        ::glm::vec3 lightPosition{ -1.0f };
        alignas(16) ::glm::vec4 lightColor{ 1.0f }; // w is intensity
    };



public:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Constructors
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    explicit AScene();



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
    virtual ~AScene();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Copy constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    AScene(
        const AScene&
    ) noexcept = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Copy assign operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    auto operator=(
        const AScene&
    ) noexcept
        -> AScene& = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Move constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    AScene(
        AScene&&
    ) noexcept = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Move assign operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    auto operator=(
        AScene&&
    ) noexcept
        -> AScene& = delete;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Virtuals
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// if return false, scene exits
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] virtual auto onUpdate()
        -> bool = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// if return false, scene exits
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] virtual auto postUpdate()
        -> bool = 0;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Getters/Setters
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto getWindow()
        -> ::vksb::Window&;

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename ComponentType
    > [[ nodiscard ]] auto getPlayerComponent()
        -> ComponentType&;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Basic
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    void run();

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto update()
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    void draw();

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    void limitFrameRate();



protected:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Member variables
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    // Vulkan
    ::vksb::Window m_window{ false };
   ::vksb::Device m_device{ m_window };

    ::std::unique_ptr<::vksb::descriptor::SetLayout> m_pDescriptorSetLayout;
    ::std::unique_ptr<::vksb::descriptor::Pool> m_pDescriptorPool;
    ::std::vector<::VkDescriptorSet> m_descriptorSets{ ::vksb::SwapChain::MAX_FRAMES_IN_FLIGHT };
    ::std::vector<::std::unique_ptr<::vksb::Buffer>> m_uboBuffers;

    ::vksb::Renderer m_renderer{ m_window, m_device };
    ::vksb::system::Render m_renderSystem;
    ::vksb::system::PointLight m_pointLightSystem;

    ::vksb::Camera m_camera;
    ::std::uint16_t m_maxFrameRate{ 60 };

    // ECS
    ::entt::registry m_registry;
    ::entt::entity m_player;

    // Others
    ::vksb::FrameInfo m_frameInfo;

};

} // namespace vksb

#include <Vksb/AScene.impl.hpp>
