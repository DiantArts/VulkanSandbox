///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <App.hpp>
#include <System/Render.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::vksb::App::App()
{
    this->loadGameOjects();
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Rule of 5
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::vksb::App::~App() = default;



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Getters/Setters
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] auto ::vksb::App::getWindow()
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
auto ::vksb::App::run()
    -> ::std::uint8_t
{
    ::vksb::system::Render renderSystem{ m_device, m_renderer.getSwapChainRenderPass() };

    ::vksb::Camera camera;
    camera.setViewDirection(::glm::vec3{ 0.0f }, ::glm::vec3{ 0.0f, 0.0f, 1.0f });

    ::xrn::Clock m_clock;

    while (!m_window.shouldClose()) {
        m_window.handleEvents(*this);

        auto newTime{ m_clock.restart() };

        float aspect{ m_renderer.getAspectRatio() };
        // camera.setOrthographicProjection(-aspect, aspect, -1.0, 1.0, -1.0, 1.0);
        camera.setPerspectiveProjection(::glm::radians(50.0f), aspect, 0.1f, 10.0f);

        if (auto commandBuffer{ m_renderer.beginFrame() }) {
            m_renderer.beginSwapChainRenderPass(commandBuffer);
            renderSystem.renderGameObjects(commandBuffer, m_gameObjects, camera);
            m_renderer.endSwapChainRenderPass(commandBuffer);
            m_renderer.endFrame();
        }
    }

    ::vkDeviceWaitIdle(m_device.device());
    return 0;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Helpers
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

static auto createCubeModel(
    ::vksb::Device& device,
    glm::vec3 offset
)
    -> std::unique_ptr<::vksb::Model>
{
    std::vector<::vksb::Model::Vertex> vertices{

        // left face (white)
        {{-.5f, -.5f, -.5f}, {.9f, .9f, .9f}},
        {{-.5f, .5f, .5f}, {.9f, .9f, .9f}},
        {{-.5f, -.5f, .5f}, {.9f, .9f, .9f}},
        {{-.5f, -.5f, -.5f}, {.9f, .9f, .9f}},
        {{-.5f, .5f, -.5f}, {.9f, .9f, .9f}},
        {{-.5f, .5f, .5f}, {.9f, .9f, .9f}},

        // right face (yellow)
        {{.5f, -.5f, -.5f}, {.8f, .8f, .1f}},
        {{.5f, .5f, .5f}, {.8f, .8f, .1f}},
        {{.5f, -.5f, .5f}, {.8f, .8f, .1f}},
        {{.5f, -.5f, -.5f}, {.8f, .8f, .1f}},
        {{.5f, .5f, -.5f}, {.8f, .8f, .1f}},
        {{.5f, .5f, .5f}, {.8f, .8f, .1f}},

        // top face (orange, remember y axis points down)
        {{-.5f, -.5f, -.5f}, {.9f, .6f, .1f}},
        {{.5f, -.5f, .5f}, {.9f, .6f, .1f}},
        {{-.5f, -.5f, .5f}, {.9f, .6f, .1f}},
        {{-.5f, -.5f, -.5f}, {.9f, .6f, .1f}},
        {{.5f, -.5f, -.5f}, {.9f, .6f, .1f}},
        {{.5f, -.5f, .5f}, {.9f, .6f, .1f}},

        // bottom face (red)
        {{-.5f, .5f, -.5f}, {.8f, .1f, .1f}},
        {{.5f, .5f, .5f}, {.8f, .1f, .1f}},
        {{-.5f, .5f, .5f}, {.8f, .1f, .1f}},
        {{-.5f, .5f, -.5f}, {.8f, .1f, .1f}},
        {{.5f, .5f, -.5f}, {.8f, .1f, .1f}},
        {{.5f, .5f, .5f}, {.8f, .1f, .1f}},

        // nose face (blue)
        {{-.5f, -.5f, 0.5f}, {.1f, .1f, .8f}},
        {{.5f, .5f, 0.5f}, {.1f, .1f, .8f}},
        {{-.5f, .5f, 0.5f}, {.1f, .1f, .8f}},
        {{-.5f, -.5f, 0.5f}, {.1f, .1f, .8f}},
        {{.5f, -.5f, 0.5f}, {.1f, .1f, .8f}},
        {{.5f, .5f, 0.5f}, {.1f, .1f, .8f}},

        // tail face (green)
        {{-.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
        {{.5f, .5f, -0.5f}, {.1f, .8f, .1f}},
        {{-.5f, .5f, -0.5f}, {.1f, .8f, .1f}},
        {{-.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
        {{.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
        {{.5f, .5f, -0.5f}, {.1f, .8f, .1f}},

    };
    for (auto& v : vertices) {
        v.position += offset;
    }
    return std::make_unique<::vksb::Model>(device, vertices);
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::App::loadGameOjects()
{
    ::vksb::GameObject cube{ createCubeModel(m_device, { 0.0f, 0.0f, 0.0f }) };
    cube.transform.translation = { 0.0f, 0.0f, 2.5f };
    cube.transform.scale = { 0.5f, 0.5f, 0.5f };
    m_gameObjects.push_back(::std::move(cube));
}
