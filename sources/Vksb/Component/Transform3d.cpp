#include <pch.hpp>
#include <Vksb/Component/Transform3d.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////
::vksb::component::Transform3d::Transform3d(
    ::std::unique_ptr<::vksb::Model>&& model
)
    : m_model{ ::std::move(model) }
{}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Matrix
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::updateMatrix(
    const ::glm::vec3& position,
    const ::glm::vec3& rotation,
    const ::glm::vec3& scale
)
{
    const float c3{ ::glm::cos(rotation.z) };
    const float s3{ ::glm::sin(rotation.z) };
    const float c2{ ::glm::cos(rotation.x) };
    const float s2{ ::glm::sin(rotation.x) };
    const float c1{ ::glm::cos(rotation.y) };
    const float s1{ ::glm::sin(rotation.y) };

    m_matrix = ::glm::mat4{
        {
            scale.x * (c1 * c3 + s1 * s2 * s3),
            scale.x * (c2 * s3),
            scale.x * (c1 * s2 * s3 - c3 * s1),
            0.0f,
        },
        {
            scale.y * (c3 * s1 * s2 - c1 * s3),
            scale.y * (c2 * c3),
            scale.y * (c1 * c3 * s2 + s1 * s3),
            0.0f,
        },
        {
            scale.z * (c2 * s1),
            scale.z * (-s2),
            scale.z * (c1 * c2),
            0.0f,
        },
        { position.x, position.y, position.z, 1.0f }
    };
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::updateMatrix(
    const ::glm::vec3& position,
    const ::glm::vec3& rotation
)
{
    const float c3{ ::glm::cos(rotation.z) };
    const float s3{ ::glm::sin(rotation.z) };
    const float c2{ ::glm::cos(rotation.x) };
    const float s2{ ::glm::sin(rotation.x) };
    const float c1{ ::glm::cos(rotation.y) };
    const float s1{ ::glm::sin(rotation.y) };

    m_matrix = ::glm::mat4{
        {
            c1 * c3 + s1 * s2 * s3,
            c2 * s3,
            c1 * s2 * s3 - c3 * s1,
            0.0f,
        }, {
            c3 * s1 * s2 - c1 * s3,
            c2 * c3,
            c1 * c3 * s2 + s1 * s3,
            0.0f,
        }, {
            c2 * s1,
            -s2,
            c1 * c2,
            0.0f,
        }, {
            position.x, position.y, position.z, 1.0f
        }
    };
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::updateMatrix(
    const ::glm::vec3& position
)
{
    const ::glm::vec3 rotation{ 0.0f };

    const float c3{ ::glm::cos(rotation.z) };
    const float s3{ ::glm::sin(rotation.z) };
    const float c2{ ::glm::cos(rotation.x) };
    const float s2{ ::glm::sin(rotation.x) };
    const float c1{ ::glm::cos(rotation.y) };
    const float s1{ ::glm::sin(rotation.y) };

    m_matrix = ::glm::mat4{
        {
            c1 * c3 + s1 * s2 * s3,
            c2 * s3,
            c1 * s2 * s3 - c3 * s1,
            0.0f,
        }, {
            c3 * s1 * s2 - c1 * s3,
            c2 * c3,
            c1 * c3 * s2 + s1 * s3,
            0.0f,
        }, {
            c2 * s1,
            -s2,
            c1 * c2,
            0.0f,
        }, {
            position.x, position.y, position.z, 1.0f
        }
    };
}

///////////////////////////////////////////////////////////////////////////
auto ::vksb::component::Transform3d::getMatrix() const
    -> const ::glm::mat4&
{
    return m_matrix;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Normal Matrix
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::updateNormalMatrix(
    const ::glm::vec3& rotation,
    const ::glm::vec3& scale
)
{
    const float c3{ ::glm::cos(rotation.z) };
    const float s3{ ::glm::sin(rotation.z) };
    const float c2{ ::glm::cos(rotation.x) };
    const float s2{ ::glm::sin(rotation.x) };
    const float c1{ ::glm::cos(rotation.y) };
    const float s1{ ::glm::sin(rotation.y) };
    const ::glm::vec3 inversedScale{ 1.0f / scale };

    m_normalMatrix = ::glm::mat3{
        {
            inversedScale.x * (c1 * c3 + s1 * s2 * s3),
            inversedScale.x * (c2 * s3),
            inversedScale.x * (c1 * s2 * s3 - c3 * s1),
        },
        {
            inversedScale.y * (c3 * s1 * s2 - c1 * s3),
            inversedScale.y * (c2 * c3),
            inversedScale.y * (c1 * c3 * s2 + s1 * s3),
        },
        {
            inversedScale.z * (c2 * s1),
            inversedScale.z * (-s2),
            inversedScale.z * (c1 * c2),
        }
    };
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Transform3d::updateNormalMatrix(
    const ::glm::vec3& rotation
)
{
    return this->updateNormalMatrix(rotation, ::glm::vec3{ 1.0f });
}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////
auto ::vksb::component::Transform3d::getNormalMatrix() const
    -> const ::glm::mat3&
{
    return m_normalMatrix;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// View
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
auto ::vksb::component::Transform3d::getView(
    const ::glm::vec3& position,
    const ::glm::vec3& direction
) const
    -> ::glm::mat4
{
    return ::glm::lookAt(position, position + direction, ::glm::vec3{ 0.0f, 1.0f, 0.0f });
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Model
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////
auto ::vksb::component::Transform3d::getModel() const
    -> ::vksb::Model&
{
    return *m_model;
}
