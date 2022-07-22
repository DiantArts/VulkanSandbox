///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Event/KeyReleased.hpp>
#include <Component/Control.hpp>
#include <Configuration.hpp>
#include <AScene.hpp>


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::vksb::event::KeyReleased::KeyReleased(
    ::std::int16_t keyCode
)
    : m_keyCode{ keyCode }
{}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Resolve
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::event::KeyReleased::resolve(
    ::vksb::AScene& scene
)
{
    auto& playerController{ scene.getPlayerComponent<::vksb::component::Control>() };

    // move
    if (m_keyCode == ::vksb::configuration.keyBindings.moveForward) {
        playerController.stopMovingForward();
    } else if (m_keyCode == ::vksb::configuration.keyBindings.moveBackward) {
        playerController.stopMovingBackward();
    } else if (m_keyCode == ::vksb::configuration.keyBindings.moveLeft) {
        playerController.stopMovingLeft();
    } else if (m_keyCode == ::vksb::configuration.keyBindings.moveRight) {
        playerController.stopMovingRight();
    } else if (m_keyCode == ::vksb::configuration.keyBindings.moveUp) {
        playerController.stopMovingUp();
    } else if (m_keyCode == ::vksb::configuration.keyBindings.moveDown) {
        playerController.stopMovingDown();

    // move arrows
    } else if (m_keyCode == ::vksb::configuration.keyBindings.moveForward2) {
        playerController.stopMovingForward();
    } else if (m_keyCode == ::vksb::configuration.keyBindings.moveBackward2) {
        playerController.stopMovingBackward();
    } else if (m_keyCode == ::vksb::configuration.keyBindings.moveLeft2) {
        playerController.stopMovingLeft();
    } else if (m_keyCode == ::vksb::configuration.keyBindings.moveRight2) {
        playerController.stopMovingRight();

    // look
    } else if (m_keyCode == ::vksb::configuration.keyBindings.lookUp) {
    } else if (m_keyCode == ::vksb::configuration.keyBindings.lookDown) {
    } else if (m_keyCode == ::vksb::configuration.keyBindings.lookLeft) {
    } else if (m_keyCode == ::vksb::configuration.keyBindings.lookRight) {
    } else {
        ::std::cout << "this key is not bound" << ::std::endl;
    }
}
