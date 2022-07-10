#include <pch.hpp>
#include <Component/Transformable.hpp>



// ------------------------------------------------------------------ *structors

::vksb::component::Transformable::Transformable()
    : m_position{ 0.0F }
{
    this->adjustDirection();
    this->generateModel();
}

::vksb::component::Transformable::Transformable(
    const ::glm::vec3& position
)
    : m_position{ position }
{
    this->adjustDirection();
    this->generateModel();
}

::vksb::component::Transformable::Transformable(
    ::glm::vec3&& position
)
    : m_position{ ::std::move(position) }
{
    this->adjustDirection();
    this->generateModel();
}

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
    return m_model;
}


// ------------------------------------------------------------------ Position

void ::vksb::component::Transformable::moveForward(
    const float velocity
)
{
    m_position += velocity * m_direction;
    this->generateModel();
}

void ::vksb::component::Transformable::moveBackward(
    const float velocity
)
{
    m_position -= velocity * m_direction;
    this->generateModel();
}

void ::vksb::component::Transformable::moveRight(
    const float velocity
)
{
    m_position += ::glm::normalize(::glm::cross(m_direction, ::glm::vec3{ 0.0F, 1.0F, 0.0F })) * velocity;
    this->generateModel();
}

void ::vksb::component::Transformable::moveLeft(
    const float velocity
)
{
    m_position -= ::glm::normalize(::glm::cross(m_direction, ::glm::vec3{ 0.0F, 1.0F, 0.0F })) * velocity;
    this->generateModel();
}

void ::vksb::component::Transformable::moveUp(
    const float velocity
)
{
    m_position.y += velocity;
    this->generateModel();
}

void ::vksb::component::Transformable::moveDown(
    const float velocity
)
{
    m_position.y -= velocity;
    this->generateModel();
}



void ::vksb::component::Transformable::move(
    const ::glm::vec3& offset
)
{
    m_position += offset;
    this->generateModel();
}

void ::vksb::component::Transformable::move(
    const float offsetX,
    const float offsetY,
    const float offsetZ
)
{
    m_position += ::glm::vec3{ offsetX, offsetY, offsetZ };
    this->generateModel();
}

void ::vksb::component::Transformable::moveX(
    const float offset
)
{
    m_position.x += offset;
    this->generateModel();
}

void ::vksb::component::Transformable::moveY(
    const float offset
)
{
    m_position.y += offset;
    this->generateModel();
}

void ::vksb::component::Transformable::moveZ(
    const float offset
)
{
    m_position.z += offset;
    this->generateModel();
}



void ::vksb::component::Transformable::setPosition(
    const ::glm::vec3& position
)
{
    m_position = position;
    this->generateModel();
}

void ::vksb::component::Transformable::setPosition(
    ::glm::vec3&& position
)
{
    m_position = ::std::move(position);
    this->generateModel();
}

void ::vksb::component::Transformable::setPosition(
    const float positionX,
    const float positionY,
    const float positionZ
)
{
    m_position = ::glm::vec3{ positionX, positionY, positionZ };
    this->generateModel();
}

void ::vksb::component::Transformable::setPositionX(
    const float position
)
{
    m_position.x += position;
    this->generateModel();
}

void ::vksb::component::Transformable::setPositionY(
    const float position
)
{
    m_position.y += position;
    this->generateModel();
}

void ::vksb::component::Transformable::setPositionZ(
    const float position
)
{
    m_position.z += position;
    this->generateModel();
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
    m_model = ::glm::scale(m_model, m_scale);
}

void ::vksb::component::Transformable::scale(
    const ::glm::vec3& scale
)
{
    m_scale += scale;
    m_model = ::glm::scale(m_model, m_scale);
}

void ::vksb::component::Transformable::scale(
    const float scaleX,
    const float scaleY,
    const float scaleZ
)
{
    m_scale += ::glm::vec3{ scaleX, scaleY, scaleZ };
    m_model = ::glm::scale(m_model, m_scale);
}

void ::vksb::component::Transformable::scaleX(
    const float scale
)
{
    m_scale.x += scale;
    m_model = ::glm::scale(m_model, m_scale);
}

void ::vksb::component::Transformable::scaleY(
    const float scale
)
{
    m_scale.y += scale;
    m_model = ::glm::scale(m_model, m_scale);
}

void ::vksb::component::Transformable::scaleZ(
    const float scale
)
{
    m_scale.z += scale;
    m_model = ::glm::scale(m_model, m_scale);
}



void ::vksb::component::Transformable::setScale(
    const float scale
)
{
    m_scale = ::glm::vec3{ scale };
    m_model = ::glm::scale(m_model, m_scale);
}

void ::vksb::component::Transformable::setScale(
    const ::glm::vec3& scale
)
{
    m_scale = scale;
    m_model = ::glm::scale(m_model, m_scale);
}

void ::vksb::component::Transformable::setScale(
    ::glm::vec3&& scale
)
{
    m_scale = ::std::move(scale);
    m_model = ::glm::scale(m_model, m_scale);
}

void ::vksb::component::Transformable::setScale(
    const float scaleX,
    const float scaleY,
    const float scaleZ
)
{
    m_scale = ::glm::vec3{ scaleX, scaleY, scaleZ };
    m_model = ::glm::scale(m_model, m_scale);
}

void ::vksb::component::Transformable::setScaleX(
    const float scale
)
{
    m_scale.x = scale;
    m_model = ::glm::scale(m_model, m_scale);
}

void ::vksb::component::Transformable::setScaleY(
    const float scale
)
{
    m_scale.y = scale;
    m_model = ::glm::scale(m_model, m_scale);
}

void ::vksb::component::Transformable::setScaleZ(
    const float scale
)
{
    m_scale.z = scale;
    m_model = ::glm::scale(m_model, m_scale);
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
    m_rotation.x += offset.x;
    m_rotation.y += offset.y;

    if (m_rotation.x >= 360) {
        m_rotation.x -= 360;
    }
    m_model = ::glm::rotate(m_model, -::glm::radians(offset.x), ::glm::vec3{ 0.0F, 1.0F, 0.0F });
    if (m_rotation.y > this->maxPitch) {
        m_model = ::glm::rotate(
            m_model, ::glm::radians(this->maxPitch - m_rotation.y), ::glm::vec3{ 0.0F, 0.0F, 1.0F }
        );
        m_rotation.y = this->maxPitch;
    } else if (m_rotation.y < this->minPitch) {
        m_model = ::glm::rotate(
            m_model, ::glm::radians(this->minPitch - m_rotation.y), ::glm::vec3{ 0.0F, 0.0F, 1.0F }
        );
        m_rotation.y = this->minPitch;
    } else {
        m_model = ::glm::rotate(m_model, ::glm::radians(offset.y), ::glm::vec3{ 0.0F, 0.0F, 1.0F });
    }
    this->adjustDirection();
}

void ::vksb::component::Transformable::rotate(
    const float yawOffset,
    const float pitchOffset
)
{
    m_rotation.x += yawOffset;
    m_rotation.y += pitchOffset;

    if (m_rotation.x >= 360) {
        m_rotation.x -= 360;
    }
    m_model = ::glm::rotate(m_model, -::glm::radians(yawOffset), ::glm::vec3{ 0.0F, 1.0F, 0.0F });
    if (m_rotation.y > this->maxPitch) {
        m_model = ::glm::rotate(
            m_model, ::glm::radians(this->maxPitch - m_rotation.y), ::glm::vec3{ 0.0F, 0.0F, 1.0F }
        );
        m_rotation.y = this->maxPitch;
    } else if (m_rotation.y < this->minPitch) {
        m_model = ::glm::rotate(
            m_model, ::glm::radians(this->minPitch - m_rotation.y), ::glm::vec3{ 0.0F, 0.0F, 1.0F }
        );
        m_rotation.y = this->minPitch;
    } else {
        m_model = ::glm::rotate(m_model, ::glm::radians(pitchOffset), ::glm::vec3{ 0.0F, 0.0F, 1.0F });
    }
    this->adjustDirection();
}

void ::vksb::component::Transformable::rotateYaw(
    const float offset
)
{
    m_rotation.x += offset;

    if (m_rotation.x >= 360) {
        m_rotation.x -= 360;
    }
    m_model = ::glm::rotate(m_model, -::glm::radians(offset), ::glm::vec3{ 0.0F, 1.0F, 0.0F });
    this->adjustDirection();
}

void ::vksb::component::Transformable::rotatePitch(
    const float offset
)
{
    m_rotation.y += offset;

    if (m_rotation.y > this->maxPitch) {
        m_model = ::glm::rotate(
            m_model, ::glm::radians(this->maxPitch - m_rotation.y), ::glm::vec3{ 0.0F, 0.0F, 1.0F }
        );
        m_rotation.y = this->maxPitch;
    } else if (m_rotation.y < this->minPitch) {
        m_model = ::glm::rotate(
            m_model, ::glm::radians(this->minPitch - m_rotation.y), ::glm::vec3{ 0.0F, 0.0F, 1.0F }
        );
        m_rotation.y = this->minPitch;
    } else {
        m_model = ::glm::rotate(m_model, ::glm::radians(offset), ::glm::vec3{ 0.0F, 0.0F, 1.0F });
    }
    this->adjustDirection();
}



void ::vksb::component::Transformable::setRotation(
    const ::glm::vec2& rotation
)
{
    if (rotation.x >= 360 || rotation.y > this->maxPitch || rotation.y < this->minPitch) {
        throw::std::logic_error("invalid orientation");
    }
    m_model =
        ::glm::rotate(m_model, -::glm::radians(m_rotation.x - rotation.x), ::glm::vec3{ 0.0F, 1.0F, 0.0F });
    m_model =
        ::glm::rotate(m_model, ::glm::radians(m_rotation.y - rotation.y), ::glm::vec3{ 0.0F, 0.0F, 1.0F });
    m_rotation = rotation;
    this->adjustDirection();
}

void ::vksb::component::Transformable::setRotation(
    ::glm::vec2&& rotation
)
{
    if (rotation.x >= 360 || rotation.y > this->maxPitch || rotation.y < this->minPitch) {
        throw::std::logic_error("invalid orientation");
    }
    m_model =
        ::glm::rotate(m_model, -::glm::radians(m_rotation.x - rotation.x), ::glm::vec3{ 0.0F, 1.0F, 0.0F });
    m_model =
        ::glm::rotate(m_model, ::glm::radians(m_rotation.y - rotation.y), ::glm::vec3{ 0.0F, 0.0F, 1.0F });
    m_rotation = ::std::move(rotation);
    this->adjustDirection();
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
    m_model =
        ::glm::rotate(m_model, -::glm::radians(m_rotation.x - yaw), ::glm::vec3{ 0.0F, 1.0F, 0.0F });
    m_model =
        ::glm::rotate(m_model, ::glm::radians(m_rotation.y - pitch), ::glm::vec3{ 0.0F, 0.0F, 1.0F });
    this->adjustDirection();
}

void ::vksb::component::Transformable::setYaw(
    const float yaw
)
{
    if (yaw >= 360) {
        throw::std::logic_error("invalid yaw");
    }
    m_model = ::glm::rotate(m_model, -::glm::radians(m_rotation.x - yaw), ::glm::vec3{ 0.0F, 1.0F, 0.0F });
    m_rotation.x = yaw;
    this->adjustDirection();
}

void ::vksb::component::Transformable::setPitch(
    const float pitch
)
{
    if (pitch > this->maxPitch || pitch < this->minPitch) {
        throw::std::logic_error("invalid orientation");
    }
    m_model = ::glm::rotate(m_model, ::glm::radians(m_rotation.y - pitch), ::glm::vec3{ 0.0F, 0.0F, 1.0F });
    m_rotation.y = pitch;
    this->adjustDirection();
}




[[ nodiscard ]] auto ::vksb::component::Transformable::getRotation() const
    -> const ::glm::vec2&
{
    return m_rotation;
}

[[ nodiscard ]] auto ::vksb::component::Transformable::getDirection() const
    -> const ::glm::vec3&
{
    return m_direction;
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
