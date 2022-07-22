///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Event/KeyPressed.hpp>
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
::vksb::event::KeyPressed::KeyPressed(
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
void ::vksb::event::KeyPressed::resolve(
    ::vksb::AScene& scene
)
{
    auto& playerController{ scene.getPlayerComponent<::vksb::component::Control>() };

    // move
    if (m_keyCode == ::vksb::configuration.keyBindings.moveForward) {
        playerController.startMovingForward();
    } else if (m_keyCode == ::vksb::configuration.keyBindings.moveBackward) {
        playerController.startMovingBackward();
    } else if (m_keyCode == ::vksb::configuration.keyBindings.moveLeft) {
        playerController.startMovingLeft();
    } else if (m_keyCode == ::vksb::configuration.keyBindings.moveRight) {
        playerController.startMovingRight();
    } else if (m_keyCode == ::vksb::configuration.keyBindings.moveUp) {
        playerController.startMovingUp();
    } else if (m_keyCode == ::vksb::configuration.keyBindings.moveDown) {
        playerController.startMovingDown();

    // move arrows
    } else if (m_keyCode == ::vksb::configuration.keyBindings.moveForward2) {
        playerController.startMovingForward();
    } else if (m_keyCode == ::vksb::configuration.keyBindings.moveBackward2) {
        playerController.startMovingBackward();
    } else if (m_keyCode == ::vksb::configuration.keyBindings.moveLeft2) {
        playerController.startMovingLeft();
    } else if (m_keyCode == ::vksb::configuration.keyBindings.moveRight2) {
        playerController.startMovingRight();

    // look
    } else if (m_keyCode == ::vksb::configuration.keyBindings.lookUp) {
    } else if (m_keyCode == ::vksb::configuration.keyBindings.lookDown) {
    } else if (m_keyCode == ::vksb::configuration.keyBindings.lookLeft) {
    } else if (m_keyCode == ::vksb::configuration.keyBindings.lookRight) {
    } else {
        ::std::cout << "this key is not bound" << ::std::endl;
    }
}
