#include <pch.hpp>
#include <Engine/Core/Ecs/Component/Controllable.hpp>



// ------------------------------------------------------------------ *structors

///////////////////////////////////////////////////////////////////////////
::engine::core::ecs::component::Controllable::Controllable(
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
auto ::engine::core::ecs::component::Controllable::getSpeed() const
    -> float
{
    return m_moveSpeed;
}

///////////////////////////////////////////////////////////////////////////
void ::engine::core::ecs::component::Controllable::setSpeed(
    float speed
)
{
    m_moveSpeed = speed;
}



// ------------------------------------------------------------------ Movement State

///////////////////////////////////////////////////////////////////////////
void ::engine::core::ecs::component::Controllable::updatePosition(
    float deltaTime,
    ::engine::graphic::opengl::ecs::component::Transformable& transformable
)
{
    if (m_ableToFly) {
        this->updateFly(deltaTime, transformable);
    } else {
        this->updateRun(deltaTime, transformable);
    }
}

///////////////////////////////////////////////////////////////////////////
void ::engine::core::ecs::component::Controllable::startMovingForward()
{
    m_movementState[Controllable::MovementState::Forward] = true;
}

///////////////////////////////////////////////////////////////////////////
void ::engine::core::ecs::component::Controllable::startMovingBackward()
{
    m_movementState[Controllable::MovementState::Backward] = true;
}

///////////////////////////////////////////////////////////////////////////
void ::engine::core::ecs::component::Controllable::startMovingRight()
{
    m_movementState[Controllable::MovementState::Right] = true;
}

///////////////////////////////////////////////////////////////////////////
void ::engine::core::ecs::component::Controllable::startMovingLeft()
{
    m_movementState[Controllable::MovementState::Left] = true;
}

///////////////////////////////////////////////////////////////////////////
void ::engine::core::ecs::component::Controllable::startMovingUp()
{
    m_movementState[Controllable::MovementState::Up] = true;
}

///////////////////////////////////////////////////////////////////////////
void ::engine::core::ecs::component::Controllable::startMovingDown()
{
    m_movementState[Controllable::MovementState::Down] = true;
}

///////////////////////////////////////////////////////////////////////////
void ::engine::core::ecs::component::Controllable::stopMovingForward()
{
    m_movementState[Controllable::MovementState::Forward] = false;
}

///////////////////////////////////////////////////////////////////////////
void ::engine::core::ecs::component::Controllable::stopMovingBackward()
{
    m_movementState[Controllable::MovementState::Backward] = false;
}

///////////////////////////////////////////////////////////////////////////
void ::engine::core::ecs::component::Controllable::stopMovingRight()
{
    m_movementState[Controllable::MovementState::Right] = false;
}

///////////////////////////////////////////////////////////////////////////
void ::engine::core::ecs::component::Controllable::stopMovingLeft()
{
    m_movementState[Controllable::MovementState::Left] = false;
}

///////////////////////////////////////////////////////////////////////////
void ::engine::core::ecs::component::Controllable::stopMovingUp()
{
    m_movementState[Controllable::MovementState::Up] = false;
}

///////////////////////////////////////////////////////////////////////////
void ::engine::core::ecs::component::Controllable::stopMovingDown()
{
    m_movementState[Controllable::MovementState::Down] = false;
}

///////////////////////////////////////////////////////////////////////////
void ::engine::core::ecs::component::Controllable::stopMoving()
{
    m_movementState.reset();
}

///////////////////////////////////////////////////////////////////////////
void ::engine::core::ecs::component::Controllable::immobilize()
{
    m_movementState.reset();
}



auto ::engine::core::ecs::component::Controllable::isMovingForward() const
    -> bool
{
    return m_movementState.test(Controllable::MovementState::Forward);
}

auto ::engine::core::ecs::component::Controllable::isMovingBackward() const
    -> bool
{
    return m_movementState.test(Controllable::MovementState::Backward);
}

auto ::engine::core::ecs::component::Controllable::isMovingRight() const
    -> bool
{
    return m_movementState.test(Controllable::MovementState::Right);
}

auto ::engine::core::ecs::component::Controllable::isMovingLeft() const
    -> bool
{
    return m_movementState.test(Controllable::MovementState::Left);
}

auto ::engine::core::ecs::component::Controllable::isMovingUp() const
    -> bool
{
    return m_movementState.test(Controllable::MovementState::Up);
}

auto ::engine::core::ecs::component::Controllable::isMovingDown() const
    -> bool
{
    return m_movementState.test(Controllable::MovementState::Down);
}



// ------------------------------------------------------------------ Rotation

///////////////////////////////////////////////////////////////////////////
void ::engine::core::ecs::component::Controllable::performRotation(
    ::engine::graphic::opengl::ecs::component::Transformable& transformable
)
{
    while (m_rotateSpeed.x >= 360) {
        m_rotateSpeed.x -= 360;
    }
    transformable.rotate(::std::move(m_rotateSpeed));
    m_rotateSpeed = ::glm::vec3{ 0.0F, 0.0F, 0.0F };
}

///////////////////////////////////////////////////////////////////////////
void ::engine::core::ecs::component::Controllable::rotate(
    const ::glm::vec2& offset
)
{
    m_rotateSpeed.x += offset.x * m_sensitivity.x;
    m_rotateSpeed.y += offset.y * m_sensitivity.y;

    if (m_rotateSpeed.y > this->maxPitch) {
        m_rotateSpeed.y = this->maxPitch;
    } else if (m_rotateSpeed.y < this->minPitch) {
        m_rotateSpeed.y = this->minPitch;
    }
}

///////////////////////////////////////////////////////////////////////////
void ::engine::core::ecs::component::Controllable::rotate(
    const float yawOffset,
    const float pitchOffset
)
{
    m_rotateSpeed.x += yawOffset * m_sensitivity.x;
    m_rotateSpeed.y += pitchOffset * m_sensitivity.y;

    if (m_rotateSpeed.y > this->maxPitch) {
        m_rotateSpeed.y = this->maxPitch;
    } else if (m_rotateSpeed.y < this->minPitch) {
        m_rotateSpeed.y = this->minPitch;
    }
}

///////////////////////////////////////////////////////////////////////////
void ::engine::core::ecs::component::Controllable::rotateYaw(
    const float offset
)
{
    m_rotateSpeed.x += offset * m_sensitivity.x;
}

///////////////////////////////////////////////////////////////////////////
void ::engine::core::ecs::component::Controllable::rotatePitch(
    const float offset
)
{
    m_rotateSpeed.y += offset * m_sensitivity.y;

    if (m_rotateSpeed.y > this->maxPitch) {
        m_rotateSpeed.y = this->maxPitch;
    } else if (m_rotateSpeed.y < this->minPitch) {
        m_rotateSpeed.y = this->minPitch;
    }
}

///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] auto ::engine::core::ecs::component::Controllable::getRotation() const
    -> const ::glm::vec3&
{
    return m_rotateSpeed;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Helpers
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::engine::core::ecs::component::Controllable::updateFly(
    float deltaTime,
    ::engine::graphic::opengl::ecs::component::Transformable& transformable
)
{
}

///////////////////////////////////////////////////////////////////////////
void ::engine::core::ecs::component::Controllable::updateRun(
    float deltaTime,
    ::engine::graphic::opengl::ecs::component::Transformable& transformable
)
{
}
