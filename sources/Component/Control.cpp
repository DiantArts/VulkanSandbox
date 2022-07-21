#include <pch.hpp>
#include <Component/Control.hpp>
#include <Component/Transform3d.hpp>
#include <Configuration.hpp>


// ------------------------------------------------------------------ *structors

///////////////////////////////////////////////////////////////////////////
::vksb::component::Control::Control(
    bool ableToFly
)
    : m_ableToFly{ ableToFly }
{}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Speed
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
auto ::vksb::component::Control::getSpeed() const
    -> float
{
    return m_moveSpeed;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Control::setSpeed(
    float speed
)
{
    m_moveSpeed = speed;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Update
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Control::updatePosition(
    float deltaTime,
    ::vksb::component::Transform3d& transform
)
{
    if (m_ableToFly) {
        this->updateFly(deltaTime, transform);
    } else {
        this->updateRun(deltaTime, transform);
    }
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Start moving
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Control::startMovingForward()
{
    m_movementState[Control::MovementState::forward] = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Control::startMovingBackward()
{
    m_movementState[Control::MovementState::backward] = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Control::startMovingRight()
{
    m_movementState[Control::MovementState::right] = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Control::startMovingLeft()
{
    m_movementState[Control::MovementState::left] = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Control::startMovingUp()
{
    m_movementState[Control::MovementState::up] = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Control::startMovingDown()
{
    m_movementState[Control::MovementState::down] = true;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Stop moving
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Control::stopMovingForward()
{
    m_movementState[Control::MovementState::forward] = false;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Control::stopMovingBackward()
{
    m_movementState[Control::MovementState::backward] = false;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Control::stopMovingRight()
{
    m_movementState[Control::MovementState::right] = false;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Control::stopMovingLeft()
{
    m_movementState[Control::MovementState::left] = false;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Control::stopMovingUp()
{
    m_movementState[Control::MovementState::up] = false;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Control::stopMovingDown()
{
    m_movementState[Control::MovementState::down] = false;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Control::stopMoving()
{
    m_movementState.reset();
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Control::immobilize()
{
    m_movementState.reset();
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Check if moving
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
auto ::vksb::component::Control::isMovingForward() const
    -> bool
{
    return m_movementState.test(Control::MovementState::forward);
}

///////////////////////////////////////////////////////////////////////////
auto ::vksb::component::Control::isMovingBackward() const
    -> bool
{
    return m_movementState.test(Control::MovementState::backward);
}

///////////////////////////////////////////////////////////////////////////
auto ::vksb::component::Control::isMovingRight() const
    -> bool
{
    return m_movementState.test(Control::MovementState::right);
}

///////////////////////////////////////////////////////////////////////////
auto ::vksb::component::Control::isMovingLeft() const
    -> bool
{
    return m_movementState.test(Control::MovementState::left);
}

///////////////////////////////////////////////////////////////////////////
auto ::vksb::component::Control::isMovingUp() const
    -> bool
{
    return m_movementState.test(Control::MovementState::up);
}

///////////////////////////////////////////////////////////////////////////
auto ::vksb::component::Control::isMovingDown() const
    -> bool
{
    return m_movementState.test(Control::MovementState::down);
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Rotation
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Control::performRotation(
    ::vksb::component::Transform3d& transform
)
{
    while (::vksb::configuration.rotateSpeed.x >= 360) {
        ::vksb::configuration.rotateSpeed.x -= 360;
    }
    transform.rotate(::std::move(::vksb::configuration.rotateSpeed));
    ::vksb::configuration.rotateSpeed = ::glm::vec3{ 0.0f, 0.0f, 0.0f };
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Control::rotate(
    const ::glm::vec2& offset
)
{
    ::vksb::configuration.rotateSpeed.x += offset.x * ::vksb::configuration.mouseSensitivity.x;
    ::vksb::configuration.rotateSpeed.y += offset.y * ::vksb::configuration.mouseSensitivity.y;

    if (::vksb::configuration.rotateSpeed.y > ::vksb::configuration.maxPitch) {
        ::vksb::configuration.rotateSpeed.y = ::vksb::configuration.maxPitch;
    } else if (::vksb::configuration.rotateSpeed.y < ::vksb::configuration.minPitch) {
        ::vksb::configuration.rotateSpeed.y = ::vksb::configuration.minPitch;
    }
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Control::rotate(
    const float yawOffset,
    const float pitchOffset
)
{
    ::vksb::configuration.rotateSpeed.x += yawOffset * ::vksb::configuration.mouseSensitivity.x;
    ::vksb::configuration.rotateSpeed.y += pitchOffset * ::vksb::configuration.mouseSensitivity.y;

    if (::vksb::configuration.rotateSpeed.y > ::vksb::configuration.maxPitch) {
        ::vksb::configuration.rotateSpeed.y = ::vksb::configuration.maxPitch;
    } else if (::vksb::configuration.rotateSpeed.y < ::vksb::configuration.minPitch) {
        ::vksb::configuration.rotateSpeed.y = ::vksb::configuration.minPitch;
    }
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Control::rotateYaw(
    const float offset
)
{
    ::vksb::configuration.rotateSpeed.x += offset * ::vksb::configuration.mouseSensitivity.x;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Control::rotatePitch(
    const float offset
)
{
    ::vksb::configuration.rotateSpeed.y += offset * ::vksb::configuration.mouseSensitivity.y;

    if (::vksb::configuration.rotateSpeed.y > ::vksb::configuration.maxPitch) {
        ::vksb::configuration.rotateSpeed.y = ::vksb::configuration.maxPitch;
    } else if (::vksb::configuration.rotateSpeed.y < ::vksb::configuration.minPitch) {
        ::vksb::configuration.rotateSpeed.y = ::vksb::configuration.minPitch;
    }
}

///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] auto ::vksb::component::Control::getRotation() const
    -> const ::glm::vec3&
{
    return ::vksb::configuration.rotateSpeed;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Helpers
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Control::updateFly(
    float deltaTime,
    ::vksb::component::Transform3d& transform
)
{
    // search the number of directions moving in and removing speed when multiple direction at once
    auto speedDirectionDivider{ 2 };

    if (this->isMovingUp()) {
        if (!this->isMovingDown()) {
            speedDirectionDivider /= 2;
        }
        speedDirectionDivider /= 2;
    } else if (this->isMovingDown()) {
        speedDirectionDivider /= 2;
    }

    if (this->isMovingLeft()) {
        if (!this->isMovingRight()) {
            speedDirectionDivider /= 2;
        }
    } else if (this->isMovingRight()) {
        speedDirectionDivider /= 2;
    }

    if (this->isMovingForward()) {
        if (!this->isMovingBackward()) {
            speedDirectionDivider /= 2;
        }
    } else if (this->isMovingBackward()) {
        speedDirectionDivider /= 2;
    } else if (speedDirectionDivider == 2) {
        return; // not any direction
    }

    // apply movement
    auto velocity{ this->getSpeed() * deltaTime / speedDirectionDivider };
    if (this->isMovingForward()) {
        transform.moveForward(velocity);
    } else if (this->isMovingBackward()) {
        transform.moveBackward(velocity);
    } else if (this->isMovingLeft()) {
        transform.moveLeft(velocity);
    } else if (this->isMovingRight()) {
        transform.moveRight(velocity);
    } else if (this->isMovingUp()) {
        transform.moveUp(velocity);
    } else if (this->isMovingDown()) {
        transform.moveDown(velocity);
    }
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Control::updateRun(
    float deltaTime,
    ::vksb::component::Transform3d& transform
)
{
    // search the number of directions moving in and removing speed when multiple direction at once
    auto speedDirectionDivider{ 2 };
    if (this->isMovingForward() || this->isMovingBackward()) {
        speedDirectionDivider /= 2;
    }
    if (this->isMovingLeft() || this->isMovingRight()) {
        speedDirectionDivider /= 2;
    } else if (speedDirectionDivider == 2) {
        return; // not any direction
    }

    auto velocity{ this->getSpeed() * deltaTime / speedDirectionDivider };
    if (this->isMovingForward()) {
        transform.moveForward(velocity);
    } else if (this->isMovingBackward()) {
        transform.moveBackward(velocity);
    } else if (this->isMovingLeft()) {
        transform.moveLeft(velocity);
    } else if (this->isMovingRight()) {
        transform.moveRight(velocity);
    }
}
