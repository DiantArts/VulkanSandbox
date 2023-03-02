///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <xrn/Util.hpp>
#include <Vksb/App.hpp>
#include <Vksb/Components.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::vksb::App::App()
    : ::vksb::AScene::AScene{}
{
    this->loadObjects();
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
// Overrides
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
auto ::vksb::App::onUpdate()
    -> bool
{
    return true;
}

///////////////////////////////////////////////////////////////////////////
auto ::vksb::App::postUpdate()
    -> bool
{
    return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Helpers
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::App::loadObjects()
{
    { // player hardcoded as cube
        auto entity{ m_player };
        m_registry.emplace<::vksb::component::Transform3d>(entity, ::vksb::Model::createFromFile(m_device, "Cube"));
        m_registry.emplace<::vksb::component::Position>(entity, 0.0f, 0.4f, -1.0f);
        m_registry.emplace<::vksb::component::Scale>(entity, 0.1f);
        m_registry.emplace<::vksb::component::Rotation>(entity, ::glm::vec3{ 0.0f, 0.0f, 0.0f });
    }

    { // vase 1
        auto entity{ m_registry.create() };
        m_registry.emplace<::vksb::component::Transform3d>(entity, ::vksb::Model::createFromFile(m_device, "FlatVase"));
        m_registry.emplace<::vksb::component::Position>(entity, -0.25f, 0.5f, 0.0f);
    }

    { // vase 2
        auto entity{ m_registry.create() };
        m_registry.emplace<::vksb::component::Transform3d>(entity, ::vksb::Model::createFromFile(m_device, "SmoothVase"));
        m_registry.emplace<::vksb::component::Position>(entity, 0.25f, 0.5f, 0.0f);
    }

    { // floor
        auto entity{ m_registry.create() };
        m_registry.emplace<::vksb::component::Transform3d>(entity, ::vksb::Model::createFromFile(m_device, "Floor"));
        m_registry.emplace<::vksb::component::Position>(entity, 0.0f, 0.5f, 0.0f);
    }

    { // lights
        std::vector<glm::vec3> lightColors{
            { 1.f, .1f, .1f },
            { .1f, .1f, 1.f },
            { .1f, 1.f, .1f },
            { 1.f, 1.f, .1f },
            { .1f, 1.f, 1.f },
            { 1.f, 1.f, 1.f }
        };

        // create the lights at equal distances from each other in circle
        for (auto i{ 0uz }; const auto& color : lightColors) {
            auto rotation{ ::glm::rotate(
                ::glm::mat4(1.0f),
                i * ::glm::two_pi<float>() / lightColors.size(),
                { 0.0f, -1.0f, 0.0f }
            ) };
            auto entity{ m_registry.create() };
            m_registry.emplace<::vksb::component::Position>(
                entity, ::glm::vec3{ rotation * ::glm::vec4{ -0.0f, -0.0f, -0.5f, 1.0f } }
            );
            m_registry.emplace<::vksb::component::PointLight>(entity, color);
            ++i;
        }
    }
}
