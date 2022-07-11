#pragma once

#include <xrn/Ecs.hpp>
#include <Window.hpp>
#include <Device.hpp>
#include <Renderer.hpp>
#include <GameObject.hpp>
#include <Camera.hpp>

namespace vksb {

///////////////////////////////////////////////////////////////////////////
/// \brief No clue what it does xD
/// \ingroup vulkan
///
/// \include App.hpp <App.hpp>
///
///////////////////////////////////////////////////////////////////////////
class App {

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
    explicit App();



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
    ~App();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Copy constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    App(
        const App&
    ) noexcept = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Copy assign operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    auto operator=(
        const App&
    ) noexcept
        -> App& = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Move constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    App(
        App&&
    ) noexcept = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Move assign operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    auto operator=(
        App&&
    ) noexcept
        -> App& = delete;



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
        ::xrn::ecs::detail::constraint::isComponent ComponentType
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
    [[ nodiscard ]] auto run()
        -> ::std::uint8_t;



private:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Helpers
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    void loadGameOjects();



private:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Member variables
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    // ECS
    ::xrn::ecs::component::Container m_components{ 10 };
    ::xrn::ecs::entity::Container m_entities{ m_components };
    ::xrn::ecs::system::Container m_systems;
    ::xrn::ecs::system::ConstContainer m_constSystems;

    // Vulkan
    ::vksb::Window m_window{ false };
    ::vksb::Device m_device{ m_window };
    ::vksb::Renderer m_renderer{ m_window, m_device };

    // Others
    ::std::vector<::vksb::GameObject> m_gameObjects;
    ::std::size_t m_playerIndex{ 0 };


};

} // namespace vksb

#include <App.impl.hpp>
