#include <pch.hpp>
#include <Vksb/Component/Control.hpp>
#include <Vksb/Component/Transform3d.hpp>
#include <Vksb/Configuration.hpp>


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
    // search the number of directions moving in and removing speed when multiple direction at once
    auto speedDirectionDivider{ 1.0f };

    // bot top
    if (m_ableToFly) {
        if (this->isMovingUp()) {
            if (!this->isMovingDown()) {
                speedDirectionDivider /= 2;
            }
            speedDirectionDivider /= 2;
        } else if (this->isMovingDown()) {
            speedDirectionDivider /= 2;
        }
    }

    // left right
    if (this->isMovingLeft()) {
        if (!this->isMovingRight()) {
            speedDirectionDivider /= 2;
        }
    } else if (this->isMovingRight()) {
        speedDirectionDivider /= 2;
    }

    // forward backward
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
    auto velocity{ this->getSpeed() * deltaTime * speedDirectionDivider / 10000 };

    // bot top
    if (m_ableToFly) {
        if (this->isMovingUp()) {
            if (!this->isMovingDown()) {
                // transform.moveUp(velocity);
            }
            speedDirectionDivider /= 2;
        } else if (this->isMovingDown()) {
            // transform.moveDown(velocity);
        }
    }

    // left right
    if (this->isMovingLeft()) {
        if (!this->isMovingRight()) {
            // transform.moveLeft(velocity);
        }
    } else if (this->isMovingRight()) {
        // transform.moveRight(velocity);
    }

    // forward backward
    if (this->isMovingForward()) {
        if (!this->isMovingBackward()) {
            // transform.moveForward(velocity);
        }
    } else if (this->isMovingBackward()) {
        // transform.moveBackward(velocity);
    }
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Control::updateRotation(
    ::vksb::component::Transform3d& transform
)
{
    // transform.rotate(::std::move(m_rotation));
    m_rotation = ::glm::vec3{ 0.0f, 0.0f, 0.0f };
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
void ::vksb::component::Control::rotate(
    const ::glm::vec3& offset
)
{
    m_rotation += offset;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Control::rotate(
    const float rotationXOffset,
    const float rotationYOffset,
    const float rotationZOffset
)
{
    m_rotation.x += rotationXOffset * ::vksb::configuration.sensitivity.x;
    m_rotation.y += rotationYOffset * ::vksb::configuration.sensitivity.y;
    m_rotation.z += rotationZOffset * ::vksb::configuration.sensitivity.z;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Control::rotateX(
    const float offset
)
{
    m_rotation.x += offset * ::vksb::configuration.sensitivity.x;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Control::rotateY(
    const float offset
)
{
    m_rotation.y += offset * ::vksb::configuration.sensitivity.y;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Control::rotateZ(
    const float offset
)
{
    m_rotation.y += offset * ::vksb::configuration.sensitivity.z;
}
