///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Event/KeyPressed.hpp>
#include <Configuration.hpp>
#include <App.hpp>


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::vksb::event::KeyPressed::KeyPressed(
    ::std::int16_t keyCode
)
    : m_keyCode{ keyCode }
{}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Rule of 5
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::vksb::event::KeyPressed::~KeyPressed() = default;

///////////////////////////////////////////////////////////////////////////
::vksb::event::KeyPressed::KeyPressed(
    ::vksb::event::KeyPressed&&
) noexcept = default;

///////////////////////////////////////////////////////////////////////////
auto ::vksb::event::KeyPressed::operator=(
    ::vksb::event::KeyPressed&&
) noexcept
    -> ::vksb::event::KeyPressed& = default;



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Resolve
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::event::KeyPressed::resolve(
    ::vksb::App& app
)
{
    // move
    if (m_keyCode == ::vksb::configuration.keyBindings.moveForward) {
    } else if (m_keyCode == ::vksb::configuration.keyBindings.moveBackward) {
    } else if (m_keyCode == ::vksb::configuration.keyBindings.moveLeft) {
    } else if (m_keyCode == ::vksb::configuration.keyBindings.moveRight) {
    } else if (m_keyCode == ::vksb::configuration.keyBindings.moveUp) {
    } else if (m_keyCode == ::vksb::configuration.keyBindings.moveDown) {

    // move arrows
    } else if (m_keyCode == ::vksb::configuration.keyBindings.moveForward2) {
    } else if (m_keyCode == ::vksb::configuration.keyBindings.moveBackward2) {
    } else if (m_keyCode == ::vksb::configuration.keyBindings.moveLeft2) {
    } else if (m_keyCode == ::vksb::configuration.keyBindings.moveRight2) {

    // look
    } else if (m_keyCode == ::vksb::configuration.keyBindings.lookUp) {
    } else if (m_keyCode == ::vksb::configuration.keyBindings.lookDown) {
    } else if (m_keyCode == ::vksb::configuration.keyBindings.lookLeft) {
    } else if (m_keyCode == ::vksb::configuration.keyBindings.lookRight) {
    } else {
        ::std::cout << "this key is not bound" << ::std::endl;
    }
}
