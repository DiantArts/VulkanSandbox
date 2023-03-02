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
    auto* playerController{ scene.tryGetPlayerComponent<::vksb::component::Control>() };

    // if player is controllable
    if (playerController) {

        // move
        if (m_keyCode == ::vksb::configuration.keyBinding.moveForward) {
            return playerController->stopMovingForward();
        } else if (m_keyCode == ::vksb::configuration.keyBinding.moveBackward) {
            return playerController->stopMovingBackward();
        } else if (m_keyCode == ::vksb::configuration.keyBinding.moveLeft) {
            return playerController->stopMovingLeft();
        } else if (m_keyCode == ::vksb::configuration.keyBinding.moveRight) {
            return playerController->stopMovingRight();
        } else if (m_keyCode == ::vksb::configuration.keyBinding.moveUp) {
            return playerController->stopMovingUp();
        } else if (m_keyCode == ::vksb::configuration.keyBinding.moveDown) {
            return playerController->stopMovingDown();

        // move arrows
        } else if (m_keyCode == ::vksb::configuration.keyBinding.moveForward2) {
            return playerController->stopMovingForward();
        } else if (m_keyCode == ::vksb::configuration.keyBinding.moveBackward2) {
            return playerController->stopMovingBackward();
        } else if (m_keyCode == ::vksb::configuration.keyBinding.moveLeft2) {
            return playerController->stopMovingLeft();
        } else if (m_keyCode == ::vksb::configuration.keyBinding.moveRight2) {
            return playerController->stopMovingRight();

        // look
        } else if (m_keyCode == ::vksb::configuration.keyBinding.lookUp) {
            return;
        } else if (m_keyCode == ::vksb::configuration.keyBinding.lookDown) {
            return;
        } else if (m_keyCode == ::vksb::configuration.keyBinding.lookLeft) {
            return;
        } else if (m_keyCode == ::vksb::configuration.keyBinding.lookRight) {
            return;
        }
    }

    XRN_ERROR("this key is not bound");
}
