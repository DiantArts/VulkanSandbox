#include <pch.hpp>
#include <Component/Transform3d.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Position
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::moveForward(
    const float velocity
)
{
    m_position += velocity * this->getDirection();
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::moveBackward(
    const float velocity
)
{
    m_position -= velocity * this->getDirection();
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::moveRight(
    const float velocity
)
{
    m_position += ::glm::normalize(::glm::cross(this->getDirection(), ::glm::vec3{ 0.0f, 1.0f, 0.0f })) * velocity;
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::moveLeft(
    const float velocity
)
{
    m_position -= ::glm::normalize(::glm::cross(this->getDirection(), ::glm::vec3{ 0.0f, 1.0f, 0.0f })) * velocity;
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::moveUp(
    const float velocity
)
{
    m_position.y -= velocity;
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::moveDown(
    const float velocity
)
{
    m_position.y += velocity;
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::move(
    const ::glm::vec3& offset
)
{
    m_position += offset;
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::move(
    const float offsetX,
    const float offsetY,
    const float offsetZ
)
{
    m_position += ::glm::vec3{ offsetX, offsetY, offsetZ };
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::moveX(
    const float offset
)
{
    m_position.x += offset;
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::moveY(
    const float offset
)
{
    m_position.y -= offset;
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::moveZ(
    const float offset
)
{
    m_position.z += offset;
    m_isMatrixChanged = true;
}



///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::setPosition(
    ::glm::vec3 position
)
{
    m_position = ::std::move(position);
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::setPosition(
    const float positionX,
    const float positionY,
    const float positionZ
)
{
    m_position = ::glm::vec3{ positionX, positionY, positionZ };
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::setPositionX(
    const float position
)
{
    m_position.x = position;
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::setPositionY(
    const float position
)
{
    m_position.y = position;
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::setPositionZ(
    const float position
)
{
    m_position.z = position;
    m_isMatrixChanged = true;
}



///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] auto ::vksb::component::Transform3d::getPosition() const
    -> const ::glm::vec3&
{
    return m_position;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Scale
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::scale(
    const float scale
)
{
    m_scale += ::glm::vec3{ scale };
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::scale(
    const ::glm::vec3& scale
)
{
    m_scale += scale;
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::scale(
    const float scaleX,
    const float scaleY,
    const float scaleZ
)
{
    m_scale += ::glm::vec3{ scaleX, scaleY, scaleZ };
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::scaleX(
    const float scale
)
{
    m_scale.x += scale;
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::scaleY(
    const float scale
)
{
    m_scale.y += scale;
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::scaleZ(
    const float scale
)
{
    m_scale.z += scale;
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::setScale(
    const float scale
)
{
    m_scale = ::glm::vec3{ scale };
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::setScale(
    const ::glm::vec3& scale
)
{
    m_scale = ::std::move(scale);
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::setScale(
    const float scaleX,
    const float scaleY,
    const float scaleZ
)
{
    m_scale = ::glm::vec3{ scaleX, scaleY, scaleZ };
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::setScaleX(
    const float scale
)
{
    m_scale.x = scale;
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::setScaleY(
    const float scale
)
{
    m_scale.y = scale;
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::setScaleZ(
    const float scale
)
{
    m_scale.z = scale;
    m_isMatrixChanged = true;
}



///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] auto ::vksb::component::Transform3d::getScale() const
    -> const ::glm::vec3&
{
    return m_scale;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Rotation
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::rotate(
    const ::glm::vec3& offset
)
{
    if (offset.x) {
        this->rotateX(offset.x);
    }
    if (offset.y) {
        this->rotateY(offset.y);
    }
    if (offset.z) {
        this->rotateZ(offset.z);
    }
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::rotate(
    const float rotationXOffset,
    const float rotationYOffset,
    const float rotationZOffset
)
{
    if (rotationXOffset) {
        this->rotateX(rotationXOffset);
    }
    if (rotationYOffset) {
        this->rotateY(rotationYOffset);
    }
    if (rotationZOffset) {
        this->rotateZ(rotationZOffset);
    }
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::rotateX(
    const float offset
)
{
    m_rotation.x += offset;
    while (m_rotation.x >= 360) {
        m_rotation.x -= 360;
    }
    m_isDirectionChanged = true;
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::rotateY(
    const float offset
)
{
    m_rotation.y += offset;
    while (m_rotation.y >= 360) {
        m_rotation.y -= 360;
    }
    m_isDirectionChanged = true;
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::rotateZ(
    const float offset
)
{
    m_rotation.z += offset;
    while (m_rotation.z >= 360) {
        m_rotation.z -= 360;
    }
    m_isDirectionChanged = true;
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::setRotation(
    ::glm::vec3 rotation
)
{
    m_rotation = ::std::move(rotation);
    while (m_rotation.x >= 360) {
        m_rotation.x -= 360;
    }
    while (m_rotation.y >= 360) {
        m_rotation.y -= 360;
    }
    while (m_rotation.z >= 360) {
        m_rotation.z -= 360;
    }
    m_isDirectionChanged = true;
    m_isMatrixChanged = true;
}


///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::setRotation(
    const float rotationX,
    const float rotationY,
    const float rotationZ
)
{
    m_rotation = ::glm::vec3{ rotationX, rotationY, rotationZ };
    while (m_rotation.x >= 360) {
        m_rotation.x -= 360;
    }
    while (m_rotation.y >= 360) {
        m_rotation.y -= 360;
    }
    while (m_rotation.z >= 360) {
        m_rotation.z -= 360;
    }
    m_isDirectionChanged = true;
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::setRotationX(
    const float rotationX
)
{
    m_rotation.x = rotationX;
    while (m_rotation.x >= 360) {
        m_rotation.x -= 360;
    }
    m_isDirectionChanged = true;
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::setRotationY(
    const float rotationY
)
{
    m_rotation.y = rotationY;
    while (m_rotation.y >= 360) {
        m_rotation.y -= 360;
    }
    m_isDirectionChanged = true;
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::setRotationZ(
    const float rotationZ
)
{
    m_rotation.y = rotationZ;
    while (m_rotation.z >= 360) {
        m_rotation.z -= 360;
    }
    m_isDirectionChanged = true;
    m_isMatrixChanged = true;
}

///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] auto ::vksb::component::Transform3d::getRotation() const
    -> const ::glm::vec3&
{
    return m_rotation;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Matrix
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::updateMatrix()
{
    const float c3{ glm::cos(m_rotation.z) };
    const float s3{ glm::sin(m_rotation.z) };
    const float c2{ glm::cos(m_rotation.x) };
    const float s2{ glm::sin(m_rotation.x) };
    const float c1{ glm::cos(m_rotation.y) };
    const float s1{ glm::sin(m_rotation.y) };
    m_matrix = glm::mat4{
        {
            m_scale.x * (c1 * c3 + s1 * s2 * s3),
            m_scale.x * (c2 * s3),
            m_scale.x * (c1 * s2 * s3 - c3 * s1),
            0.0f,
        },
        {
            m_scale.y * (c3 * s1 * s2 - c1 * s3),
            m_scale.y * (c2 * c3),
            m_scale.y * (c1 * c3 * s2 + s1 * s3),
            0.0f,
        },
        {
            m_scale.z * (c2 * s1),
            m_scale.z * (-s2),
            m_scale.z * (c1 * c2),
            0.0f,
        },
        { m_position.x, m_position.y, m_position.z, 1.0f }
    };
    m_isMatrixChanged = false;
}

///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] auto ::vksb::component::Transform3d::getMatrix()
    -> const ::glm::mat4&
{
    if (m_isMatrixChanged) {
        this->updateMatrix();
    }
    return m_matrix;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Direction
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::updateDirection()
{
    m_direction = ::glm::normalize(::glm::vec3(
        cos(::glm::radians(m_rotation.x)) * cos(::glm::radians(m_rotation.y)),
        sin(::glm::radians(m_rotation.y)),
        sin(::glm::radians(m_rotation.x)) * cos(::glm::radians(m_rotation.y))
    ));
    m_isDirectionChanged = false;
}

///////////////////////////////////////////////////////////////////////////
auto ::vksb::component::Transform3d::getDirection()
    -> const ::glm::vec3&
{
    if (m_isDirectionChanged) {
        this->updateDirection();
    }
    return m_direction;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// View
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
auto ::vksb::component::Transform3d::getView()
    -> ::glm::mat4
{
    return ::glm::lookAt(m_position, m_position + this->getDirection(), ::glm::vec3{ 0.0f, 1.0f, 0.0f });
}
