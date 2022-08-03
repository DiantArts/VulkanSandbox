///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Vksb/Window.hpp>
#include <Vksb/Event/WindowResize.hpp>
#include <Vksb/Event/KeyPressed.hpp>
#include <Vksb/Event/KeyReleased.hpp>
#include <Vksb/Event/MouseMoved.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// static elements
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
auto ::vksb::Window::Size::isValid()
    -> bool
{
    return !(!this->width || !this->height);
}

///////////////////////////////////////////////////////////////////////////
::vksb::Window::Size::operator VkExtent2D() const
{
    return { .width = static_cast<::std::uint32_t>(width), .height = static_cast<::std::uint32_t>(height) };
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::vksb::Window::Window(
    bool isFullscreen, /* = true */
    const ::std::string& windowName /* = Window::defaultName */
)
    : m_size{ Window::defaultSize }
    , m_pWindow{ ::glfwCreateWindow(
        m_size.width,
        m_size.height,
        windowName.c_str(),
        isFullscreen ? ::glfwGetPrimaryMonitor() : nullptr,
        nullptr
    ) }
{
    XRN_ASSERT(!!m_pWindow, "Create glfw window");

    ::glfwSetWindowUserPointer(m_pWindow.get(), &m_events);

    // setup callbacks
    ::glfwSetFramebufferSizeCallback(m_pWindow.get(), Window::framebufferResizeCallback);
    ::glfwSetKeyCallback(m_pWindow.get(), Window::keyCallback);
    glfwSetCursorPos(m_pWindow.get(), m_size.x, m_size.y);
    ::glfwSetCursorPosCallback(m_pWindow.get(), Window::mouseMovedCallback);

    // ::glfwSetScrollCallback(m_pWindow.get(), Window::mouseScrollcallback);
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Rule of 5
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::vksb::Window::~Window() = default;

///////////////////////////////////////////////////////////////////////////
::vksb::Window::Window(
    Window&&
) noexcept = default;

///////////////////////////////////////////////////////////////////////////
auto ::vksb::Window::operator=(
    Window&&
) noexcept
    -> Window& = default;



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Basic operations
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
auto ::vksb::Window::shouldClose() const
    -> bool
{
    return ::glfwWindowShouldClose(m_pWindow.get()) || m_shouldClose;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::Window::clear() const
{
    // ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::Window::close()
{
    ::glfwSetWindowShouldClose(m_pWindow.get(), GLFW_TRUE);
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::Window::display() const
{
    // ::glfwSwapBuffers(m_pWindow.get());
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::Window::handleEvents(
    ::vksb::AScene& app
)
{
    ::glfwPollEvents();
    m_events.resolve(app);
}

///////////////////////////////////////////////////////////////////////////
auto ::vksb::Window::wasResized()
    -> bool
{
    return m_framebufferResized;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::Window::resetResizedFlag()
{
    m_framebufferResized = false;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::Window::setResizedFlag()
{
    m_framebufferResized = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::Window::resize(
    const Window::Size& size
)
{
    m_size.width = size.width;
    m_size.height = size.height;
    this->setResizedFlag();
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Other
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
auto ::vksb::Window::getSize() const
    -> const Window::Size&
{
    return m_size;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Vulkan implementation
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::Window::createWindowSurface(
    ::VkInstance instance,
    ::VkSurfaceKHR* surface
)
{
    XRN_ASSERT(
        ::glfwCreateWindowSurface(instance, m_pWindow.get(), nullptr, surface) == VK_SUCCESS,
        "Create glfw window surface"
    );
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// GLFW callbacks
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::Window::framebufferResizeCallback(
    ::GLFWwindow* pWindow,
    const int width,
    const int height
) {
    auto& events{ *reinterpret_cast<::vksb::event::Container*>(::glfwGetWindowUserPointer(pWindow)) };
    events.emplace<::vksb::event::WindowResize>(Window::Size{
        .width = static_cast<::std::size_t>(width),
        .height = static_cast<::std::size_t>(height)
    });
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::Window::keyCallback(
    GLFWwindow* pWindow,
    const int keyCode,
    const int scancode,
    const int action,
    const int mods
)
{
    auto& events{ *reinterpret_cast<::vksb::event::Container*>(::glfwGetWindowUserPointer(pWindow)) };
    if (action == GLFW_PRESS) {
        events.emplace<::vksb::event::KeyPressed>(keyCode);
    } else if (action == GLFW_RELEASE) {
        events.emplace<::vksb::event::KeyReleased>(keyCode);
    }
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::Window::mouseMovedCallback(
    GLFWwindow* pWindow,
    const double xPos,
    const double yPos
)
{
    auto& events{ *reinterpret_cast<::vksb::event::Container*>(::glfwGetWindowUserPointer(pWindow)) };
    ::std::size_t width, height;
    glfwGetWindowSize(&width, &height);
    events.emplace<::vksb::event::MouseMoved>(xPos - width / 2, yPos - height / 2);
    glfwSetCursorPos(pWindow, width / 2, height / 2);

}

void ::vksb::Window::mouseScrollcallback(
    GLFWwindow*,
    const double,
    const double yOffset
)
{}





///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// GLFW memory
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::Window::Deleter::operator()(
    ::GLFWwindow* pWindow
)
{
    ::glfwDestroyWindow(pWindow);
}

///////////////////////////////////////////////////////////////////////////
class GlfwMemoryManager {
    GlfwMemoryManager()
    {
        XRN_ASSERT(::glfwInit(), "Init glfw");
        ::glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        ::glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        // stbi_set_flip_vertically_on_load(true);
    }

    ~GlfwMemoryManager()
    {
        ::glfwTerminate();
    }

    static const GlfwMemoryManager _;
};
const ::GlfwMemoryManager GlfwMemoryManager::_;
