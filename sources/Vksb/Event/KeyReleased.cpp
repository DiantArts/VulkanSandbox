///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Vksb/Event/KeyReleased.hpp>
#include <Vksb/Component/Control.hpp>
#include <Vksb/Configuration.hpp>
#include <Vksb/AScene.hpp>


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
    if (m_keyCode == ::vksb::configuration.keyBinding.moveForward) {
        playerController.stopMovingForward();
    } else if (m_keyCode == ::vksb::configuration.keyBinding.moveBackward) {
        playerController.stopMovingBackward();
    } else if (m_keyCode == ::vksb::configuration.keyBinding.moveLeft) {
        playerController.stopMovingLeft();
    } else if (m_keyCode == ::vksb::configuration.keyBinding.moveRight) {
        playerController.stopMovingRight();
    } else if (m_keyCode == ::vksb::configuration.keyBinding.moveUp) {
        playerController.stopMovingUp();
    } else if (m_keyCode == ::vksb::configuration.keyBinding.moveDown) {
        playerController.stopMovingDown();

    // move arrows
    } else if (m_keyCode == ::vksb::configuration.keyBinding.moveForward2) {
        playerController.stopMovingForward();
    } else if (m_keyCode == ::vksb::configuration.keyBinding.moveBackward2) {
        playerController.stopMovingBackward();
    } else if (m_keyCode == ::vksb::configuration.keyBinding.moveLeft2) {
        playerController.stopMovingLeft();
    } else if (m_keyCode == ::vksb::configuration.keyBinding.moveRight2) {
        playerController.stopMovingRight();

    // look
    } else if (m_keyCode == ::vksb::configuration.keyBinding.lookUp) {
    } else if (m_keyCode == ::vksb::configuration.keyBinding.lookDown) {
    } else if (m_keyCode == ::vksb::configuration.keyBinding.lookLeft) {
    } else if (m_keyCode == ::vksb::configuration.keyBinding.lookRight) {
    } else {
        ::std::cout << "this key is not bound" << ::std::endl;
    }
}
