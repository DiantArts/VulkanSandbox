///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Window.hpp>

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
    , m_window{ glfwCreateWindow(
        m_size.width,
        m_size.height,
        windowName.c_str(),
        isFullscreen ? glfwGetPrimaryMonitor() : nullptr,
        nullptr
    ) }
{
    if (!m_window) {
        glfwTerminate();
        throw::std::runtime_error("Window creation Failed");
    }

    glfwSetWindowUserPointer(m_window.get(), this);
    glfwSetFramebufferSizeCallback(m_window.get(), Window::framebufferResizeCallback);

    // glfwMakeContextCurrent(&*m_window);
    // glfwSetFramebufferSizeCallback(&*m_window, ::engine::graphic::opengl::detail::framebufferSizeCallback);

    // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        // glfwTerminate();
        // throw::std::runtime_error("glad initialization Failed");
    // }

    // ::engine::graphic::opengl::detail::applyDefaultConfiguration(&*m_window, m_events);
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
    return ::glfwWindowShouldClose(m_window.get()) || m_shouldClose;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::Window::clear() const
{
    // ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::Window::display() const
{
    // ::glfwSwapBuffers(m_window.get());
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::Window::handleEvents()
{
    ::glfwPollEvents();
}

///////////////////////////////////////////////////////////////////////////
auto ::vksb::Window::wasResized()
    -> bool
{
    return m_framebufferResized;
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
    ::std::cout << "Window resized." << ::std::endl;
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
    if (::glfwCreateWindowSurface(instance, m_window.get(), nullptr, surface) != VK_SUCCESS) {
        throw ::std::runtime_error{ "Failed to create window surface" };
    }
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// GLFW callbacks
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::Window::framebufferResizeCallback(
    ::GLFWwindow* windowPtr,
    int width,
    int height
) {
    auto& window{ *reinterpret_cast<::vksb::Window*>(glfwGetWindowUserPointer(windowPtr)) };
    window.resize({
        .width = static_cast<::std::size_t>(width),
        .height = static_cast<::std::size_t>(height)
    });
}




///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// GLFW memory
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::Window::Deleter::operator()(
    ::GLFWwindow* window
)
{
    ::glfwDestroyWindow(window);
}

///////////////////////////////////////////////////////////////////////////
class GlfwMemoryManager {
    GlfwMemoryManager()
    {
        if (!glfwInit()) {
            throw::std::runtime_error("glwfInit Failed");
        }
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        // stbi_set_flip_vertically_on_load(true);
    }

    ~GlfwMemoryManager()
    {
        glfwTerminate();
    }

    static const GlfwMemoryManager _;
};
const ::GlfwMemoryManager GlfwMemoryManager::_;
