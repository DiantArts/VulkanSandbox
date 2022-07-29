///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Vksb/Event/WindowResize.hpp>
#include <Vksb/Configuration.hpp>
#include <Vksb/AScene.hpp>


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::vksb::event::WindowResize::WindowResize(
    ::vksb::Window::Size size
)
    : m_size{ ::std::move(size) }
{}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Rule of 5
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::vksb::event::WindowResize::~WindowResize() = default;

///////////////////////////////////////////////////////////////////////////
::vksb::event::WindowResize::WindowResize(
    ::vksb::event::WindowResize&&
) noexcept = default;

///////////////////////////////////////////////////////////////////////////
auto ::vksb::event::WindowResize::operator=(
    ::vksb::event::WindowResize&&
) noexcept
    -> ::vksb::event::WindowResize& = default;



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Resolve
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::event::WindowResize::resolve(
    ::vksb::AScene& scene
)
{
    scene.getWindow().resize(::std::move(m_size));
}