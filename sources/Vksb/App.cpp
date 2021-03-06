///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <xrn/Util.hpp>
#include <Vksb/App.hpp>
#include <Vksb/Component/Control.hpp>



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
    {
        ::vksb::component::Transform3d object;
        object.model = ::vksb::Model::createFromFile(m_device, "SmoothVase");
        object.setPosition(-0.5f, 0.5f, 0.0f);
        object.setScale(3.0f, 1.5f, 3.0f);
        m_registry.emplace<::vksb::component::Transform3d>(m_player, ::std::move(object));
    }
    {
        ::vksb::component::Transform3d object;
        object.model = ::vksb::Model::createFromFile(m_device, "SmoothVase");
        object.setPosition(0.5f, 0.5f, 0.0f);
        object.setScale(3.0f, 1.5f, 3.0f);
        m_registry.emplace<::vksb::component::Transform3d>(m_registry.create(), ::std::move(object));
    }
    {
        ::vksb::component::Transform3d object;
        object.model = ::vksb::Model::createFromFile(m_device, "Floor");
        object.setPosition(0.0f, 0.5f, 0.0f);
        object.setScale(3.0f, 1.0f, 3.0f);
        m_registry.emplace<::vksb::component::Transform3d>(m_registry.create(), ::std::move(object));
    }
}
