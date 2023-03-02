///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Vksb/Event/KeyPressed.hpp>
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
    auto* playerController{ scene.tryGetPlayerComponent<::vksb::component::Control>() };

    // default
    if (m_keyCode == ::vksb::configuration.keyBinding.closeWindow) {
        return scene.getWindow().close();
    }

    // if player is controllable
    if (playerController) {
        // move
        if (m_keyCode == ::vksb::configuration.keyBinding.moveForward) {
            return playerController->startMovingForward();
        } else if (m_keyCode == ::vksb::configuration.keyBinding.moveBackward) {
            return playerController->startMovingBackward();
        } else if (m_keyCode == ::vksb::configuration.keyBinding.moveLeft) {
            return playerController->startMovingLeft();
        } else if (m_keyCode == ::vksb::configuration.keyBinding.moveRight) {
            return playerController->startMovingRight();
        } else if (m_keyCode == ::vksb::configuration.keyBinding.moveUp) {
            return playerController->startMovingUp();
        } else if (m_keyCode == ::vksb::configuration.keyBinding.moveDown) {
            return playerController->startMovingDown();

        // move arrows
        } else if (m_keyCode == ::vksb::configuration.keyBinding.moveForward2) {
            return playerController->startMovingForward();
        } else if (m_keyCode == ::vksb::configuration.keyBinding.moveBackward2) {
            return playerController->startMovingBackward();
        } else if (m_keyCode == ::vksb::configuration.keyBinding.moveLeft2) {
            return playerController->startMovingLeft();
        } else if (m_keyCode == ::vksb::configuration.keyBinding.moveRight2) {
            return playerController->startMovingRight();

        // look
        } else if (m_keyCode == ::vksb::configuration.keyBinding.lookUp) {
            return playerController->rotateZ(-45 / 2);
        } else if (m_keyCode == ::vksb::configuration.keyBinding.lookDown) {
            return playerController->rotateZ(45 / 2);
        } else if (m_keyCode == ::vksb::configuration.keyBinding.lookLeft) {
            return playerController->rotateX(45 / 2);
        } else if (m_keyCode == ::vksb::configuration.keyBinding.lookRight) {
            return playerController->rotateX(-45 / 2);
        }

    }

    XRN_ERROR("this key is not bound");
}
