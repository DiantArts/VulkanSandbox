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
    auto& playerController{ scene.getPlayerComponent<::vksb::component::Control>() };

    // default
    if (m_keyCode == ::vksb::configuration.keyBinding.closeWindow) {
        scene.getWindow().close();

    // move
    } else if (m_keyCode == ::vksb::configuration.keyBinding.moveForward) {
        playerController.startMovingForward();
    } else if (m_keyCode == ::vksb::configuration.keyBinding.moveBackward) {
        playerController.startMovingBackward();
    } else if (m_keyCode == ::vksb::configuration.keyBinding.moveLeft) {
        playerController.startMovingLeft();
    } else if (m_keyCode == ::vksb::configuration.keyBinding.moveRight) {
        playerController.startMovingRight();
    } else if (m_keyCode == ::vksb::configuration.keyBinding.moveUp) {
        playerController.startMovingUp();
    } else if (m_keyCode == ::vksb::configuration.keyBinding.moveDown) {
        playerController.startMovingDown();

    // move arrows
    } else if (m_keyCode == ::vksb::configuration.keyBinding.moveForward2) {
        playerController.startMovingForward();
    } else if (m_keyCode == ::vksb::configuration.keyBinding.moveBackward2) {
        playerController.startMovingBackward();
    } else if (m_keyCode == ::vksb::configuration.keyBinding.moveLeft2) {
        playerController.startMovingLeft();
    } else if (m_keyCode == ::vksb::configuration.keyBinding.moveRight2) {
        playerController.startMovingRight();

    // look
    } else if (m_keyCode == ::vksb::configuration.keyBinding.lookUp) {
    } else if (m_keyCode == ::vksb::configuration.keyBinding.lookDown) {
    } else if (m_keyCode == ::vksb::configuration.keyBinding.lookLeft) {
    } else if (m_keyCode == ::vksb::configuration.keyBinding.lookRight) {
    } else {
        ::std::cout << "this key is not bound" << ::std::endl;
    }
}
