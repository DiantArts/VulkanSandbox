#include <pch.hpp>
#include <Component/Transformable.hpp>



// ------------------------------------------------------------------ *structors

::vksb::component::Transformable::Transformable()
    : m_position{ 0.0F }
{}

::vksb::component::Transformable::Transformable(
    ::glm::vec3 position
)
    : m_position{ ::std::move(position) }
{}

::vksb::component::Transformable::~Transformable() = default;



// ------------------------------------------------------------------ Move sementic

::vksb::component::Transformable::Transformable(
    Transformable&&
) noexcept = default;

auto ::vksb::component::Transformable::operator=(
    Transformable&&
) noexcept
    -> Transformable& = default;



// ------------------------------------------------------------------ Model

void ::vksb::component::Transformable::generateModel()
{
    m_model = ::glm::translate(::glm::mat4{ 1.0F }, m_position);
    m_model = ::glm::rotate(m_model, -::glm::radians(m_rotation.x), ::glm::vec3{ 0.0F, 1.0F, 0.0F });
    m_model = ::glm::rotate(m_model, ::glm::radians(m_rotation.y), ::glm::vec3{ 0.0F, 0.0F, 1.0F });
    m_model = ::glm::scale(m_model, m_scale);
}

[[ nodiscard ]] auto ::vksb::component::Transformable::getModel() const
    -> const ::glm::mat4&
{
    if (m_isRotated) {
        this->generateModel();
    }
    if (m_isModelChanged) {
        this->generateModel();
    }
    return m_model;
}


// ------------------------------------------------------------------ Position

void ::vksb::component::Transformable::moveForward(
    const float velocity
)
{
    m_position += velocity * m_direction;
    m_isModelChanged = true;
}

void ::vksb::component::Transformable::moveBackward(
    const float velocity
)
{
    m_position -= velocity * m_direction;
    m_isModelChanged = true;
}

void ::vksb::component::Transformable::moveRight(
    const float velocity
)
{
    m_position += ::glm::normalize(::glm::cross(m_direction, ::glm::vec3{ 0.0F, 1.0F, 0.0F })) * velocity;
    m_isModelChanged = true;
}

void ::vksb::component::Transformable::moveLeft(
    const float velocity
)
{
    m_position -= ::glm::normalize(::glm::cross(m_direction, ::glm::vec3{ 0.0F, 1.0F, 0.0F })) * velocity;
    m_isModelChanged = true;
}

void ::vksb::component::Transformable::moveUp(
    const float velocity
)
{
    m_position.y += velocity;
    m_isModelChanged = true;
}

void ::vksb::component::Transformable::moveDown(
    const float velocity
)
{
    m_position.y -= velocity;
    m_isModelChanged = true;
}



void ::vksb::component::Transformable::move(
    const ::glm::vec3& offset
)
{
    m_position += offset;
    m_isModelChanged = true;
}

void ::vksb::component::Transformable::move(
    const float offsetX,
    const float offsetY,
    const float offsetZ
)
{
    m_position += ::glm::vec3{ offsetX, offsetY, offsetZ };
    m_isModelChanged = true;
}

void ::vksb::component::Transformable::moveX(
    const float offset
)
{
    m_position.x += offset;
    m_isModelChanged = true;
}

void ::vksb::component::Transformable::moveY(
    const float offset
)
{
    m_position.y += offset;
    m_isModelChanged = true;
}

void ::vksb::component::Transformable::moveZ(
    const float offset
)
{
    m_position.z += offset;
    m_isModelChanged = true;
}



void ::vksb::component::Transformable::setPosition(
    ::glm::vec3 position
)
{
    m_position = ::std::move(position);
}

void ::vksb::component::Transformable::setPosition(
    const float positionX,
    const float positionY,
    const float positionZ
)
{
    m_position = ::glm::vec3{ positionX, positionY, positionZ };
    m_isModelChanged = true;
}

void ::vksb::component::Transformable::setPositionX(
    const float position
)
{
    m_position.x += position;
    m_isModelChanged = true;
}

void ::vksb::component::Transformable::setPositionY(
    const float position
)
{
    m_position.y += position;
    m_isModelChanged = true;
}

void ::vksb::component::Transformable::setPositionZ(
    const float position
)
{
    m_position.z += position;
    m_isModelChanged = true;
}



[[ nodiscard ]] auto ::vksb::component::Transformable::getPosition() const
    -> const ::glm::vec3&
{
    return m_position;
}



// ------------------------------------------------------------------ Scale

void ::vksb::component::Transformable::scale(
    const float scale
)
{
    m_scale += ::glm::vec3{ scale };
    m_isModelChanged = true;
}

void ::vksb::component::Transformable::scale(
    const ::glm::vec3& scale
)
{
    m_scale += scale;
    m_isModelChanged = true;
}

void ::vksb::component::Transformable::scale(
    const float scaleX,
    const float scaleY,
    const float scaleZ
)
{
    m_scale += ::glm::vec3{ scaleX, scaleY, scaleZ };
    m_isModelChanged = true;
}

void ::vksb::component::Transformable::scaleX(
    const float scale
)
{
    m_scale.x += scale;
    m_isModelChanged = true;
}

void ::vksb::component::Transformable::scaleY(
    const float scale
)
{
    m_scale.y += scale;
    m_isModelChanged = true;
}

void ::vksb::component::Transformable::scaleZ(
    const float scale
)
{
    m_scale.z += scale;
    m_isModelChanged = true;
}



void ::vksb::component::Transformable::setScale(
    const float scale
)
{
    m_scale = ::glm::vec3{ scale };
    m_isModelChanged = true;
}

void ::vksb::component::Transformable::setScale(
    const ::glm::vec3& scale
)
{
    m_scale = ::std::move(scale);
    m_isModelChanged = true;
}

void ::vksb::component::Transformable::setScale(
    const float scaleX,
    const float scaleY,
    const float scaleZ
)
{
    m_scale = ::glm::vec3{ scaleX, scaleY, scaleZ };
    m_isModelChanged = true;
}

void ::vksb::component::Transformable::setScaleX(
    const float scale
)
{
    m_scale.x = scale;
    m_isModelChanged = true;
}

void ::vksb::component::Transformable::setScaleY(
    const float scale
)
{
    m_scale.y = scale;
    m_isModelChanged = true;
}

void ::vksb::component::Transformable::setScaleZ(
    const float scale
)
{
    m_scale.z = scale;
    m_isModelChanged = true;
}



[[ nodiscard ]] auto ::vksb::component::Transformable::getScale() const
    -> const ::glm::vec3&
{
    return m_scale;
}



// ------------------------------------------------------------------ Rotation

void ::vksb::component::Transformable::rotate(
    const ::glm::vec2& offset
)
{
    this->rotateYaw(offset.x);
    this->rotatePitch(offset.y);

void ::vksb::component::Transformable::rotate(
    const float yawOffset,
    const float pitchOffset
)
{
    this->rotateYaw(yawOffset);
    this->rotatePitch(pitchOffset);
}

void ::vksb::component::Transformable::rotateYaw(
    const float offset
)
{
    m_rotation.x += offset;

    if (m_rotation.x >= 360) {
        m_rotation.x -= 360;
    }
    m_isRotated = true;
    m_isModelChanged = true;
}

void ::vksb::component::Transformable::rotatePitch(
    const float offset
)
{
    m_rotation.y += offset;

    if (m_rotation.y > this->maxPitch) {
        m_rotation.y = this->maxPitch;
    } else if (m_rotation.y < this->minPitch) {
        m_rotation.y = this->minPitch;
    }
    m_isRotated = true;
    m_isModelChanged = true;
}



void ::vksb::component::Transformable::setRotation(
    ::glm::vec2 rotation
)
{
    if (rotation.x >= 360 || rotation.y > this->maxPitch || rotation.y < this->minPitch) {
        throw::std::logic_error("invalid orientation");
    }
    m_rotation = ::std::move(rotation);
    m_isRotated = true;
    m_isModelChanged = true;
}


void ::vksb::component::Transformable::setRotation(
    const float yaw,
    const float pitch
)
{
    if (yaw >= 360 || pitch > this->maxPitch || pitch < this->minPitch) {
        throw::std::logic_error("invalid orientation");
    }
    m_rotation.x = yaw;
    m_rotation.y = pitch;
    m_isRotated = true;
    m_isModelChanged = true;
}

void ::vksb::component::Transformable::setYaw(
    const float yaw
)
{
    if (yaw >= 360) {
        throw::std::logic_error("invalid yaw");
    }
    m_rotation.x = yaw;
    m_isRotated = true;
    m_isModelChanged = true;
}

void ::vksb::component::Transformable::setPitch(
    const float pitch
)
{
    if (pitch > this->maxPitch || pitch < this->minPitch) {
        throw::std::logic_error("invalid orientation");
    }
    m_rotation.y = pitch;
    m_isRotated = true;
    m_isModelChanged = true;
}




[[ nodiscard ]] auto ::vksb::component::Transformable::getRotation() const
    -> const ::glm::vec2&
{
    return m_rotation;
}



// ------------------------------------------------------------------ View

auto ::vksb::component::Transformable::getView() const
    -> ::glm::mat4
{
    return ::glm::lookAt(m_position, m_position + m_direction, ::glm::vec3{ 0.0F, 1.0F, 0.0F });
}



// ------------------------------------------------------------------ Detail

void ::vksb::component::Transformable::adjustDirection()
{
    m_direction = ::glm::normalize(::glm::vec3(
        cos(::glm::radians(m_rotation.x)) * cos(::glm::radians(m_rotation.y)),
        sin(::glm::radians(m_rotation.y)),
        sin(::glm::radians(m_rotation.x)) * cos(::glm::radians(m_rotation.y))
    ));
}
