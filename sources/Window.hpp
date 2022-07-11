#pragma once

#include <Event/Container.hpp>

namespace vksb { class App; }

namespace vksb {

///////////////////////////////////////////////////////////////////////////
/// \brief Window wrapper for GLFW
/// \ingroup vulkan
///
/// \include Window.hpp <Window.hpp>
///
///////////////////////////////////////////////////////////////////////////
class Window {

public:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // static elements
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Contains the size of the window
    ///
    ///////////////////////////////////////////////////////////////////////////
    struct Size {
        ::std::size_t width;
        ::std::size_t height;

        [[ nodiscard ]] auto isValid()
            -> bool;

        [[ nodiscard ]] operator VkExtent2D() const;
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
    explicit Window(
        bool isFullscreen = true,
        const ::std::string& windowName = Window::defaultName
    );



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
    ~Window();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Copy constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    Window(
        const Window&
    ) noexcept = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Copy assign operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    auto operator=(
        const Window&
    ) noexcept
        -> Window& = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Move constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    Window(
        Window&&
    ) noexcept;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Move assign operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    auto operator=(
        Window&&
    ) noexcept
        -> Window&;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Basic operations
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether the window should be closed or not
    ///
    /// \return True if the function should be closed
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto shouldClose() const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Clears the content of the window
    ///
    /// Replace the content with the color of the clear.
    ///
    /// \see setClearColor()
    ///
    ///////////////////////////////////////////////////////////////////////////
    void clear() const;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Display the content of the window
    ///
    ///////////////////////////////////////////////////////////////////////////
    void display() const;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Pull and resolve the events
    ///
    ///////////////////////////////////////////////////////////////////////////
    void handleEvents(
        ::vksb::App& app
    );

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto wasResized()
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    void resetResizedFlag();

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    void setResizedFlag();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Resizes the window
    ///
    ///////////////////////////////////////////////////////////////////////////
    void resize(
        const Window::Size& size
    );



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Other
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets the size of the window
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto getSize() const
        -> const Window::Size&;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Vulkan implementation
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Vulkan specific
    ///
    ///////////////////////////////////////////////////////////////////////////
    void createWindowSurface(
        ::VkInstance instance,
        ::VkSurfaceKHR* surface
    );



private:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // GLFW callbacks
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    static void framebufferResizeCallback(
        GLFWwindow* pWindowPtr,
        int width,
        int height
    );

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    static void keyCallback(
        GLFWwindow* window,
        int keyCode,
        int scancode,
        int action,
        int mods
    );

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    static void mouseMovedCallback(
        GLFWwindow* window,
        double xPos,
        double yPos
    );

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    static void mouseScrollcallback(
        GLFWwindow* window,
        double xOffset,
        double yOffset
    );



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // GLFW memory
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Window delete helper
    ///
    ///////////////////////////////////////////////////////////////////////////
    class Deleter {
    public:
        void operator()(
            ::GLFWwindow* window
        );
    };



private:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Static member variables
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    static constexpr const Window::Size defaultSize{ 800uz, 600uz };
    static constexpr const auto defaultName{ "GlfwMainWindow" };



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Member variables
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    Window::Size m_size;
    bool m_framebufferResized{ false };
    ::std::unique_ptr<::GLFWwindow, Window::Deleter> m_pWindow;

    bool m_shouldClose{ false };

    ::vksb::event::Container m_events;


};

} // namespace vksb
