///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Vksb/Camera.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::vksb::Camera::Camera() = default;



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Rule of 5
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::vksb::Camera::~Camera() = default;

///////////////////////////////////////////////////////////////////////////
::vksb::Camera::Camera(
    ::vksb::Camera&&
) noexcept = default;

///////////////////////////////////////////////////////////////////////////
auto ::vksb::Camera::operator=(
    ::vksb::Camera&&
) noexcept
    -> ::vksb::Camera& = default;



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Getters/setters
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::Camera::setOrthographicProjection(
    const float left,
    const float right,
    const float top,
    const float bottom,
    const float near,
    const float far
)
{
    m_projectionMatrix = glm::mat4{1.0f};
    m_projectionMatrix[0][0] = 2.f / (right - left);
    m_projectionMatrix[1][1] = 2.f / (bottom - top);
    m_projectionMatrix[2][2] = 1.f / (far - near);
    m_projectionMatrix[3][0] = -(right + left) / (right - left);
    m_projectionMatrix[3][1] = -(bottom + top) / (bottom - top);
    m_projectionMatrix[3][2] = -near / (far - near);
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::Camera::setPerspectiveProjection(
    const float fovY,
    const float aspect,
    const float near,
    const float far
)
{
    XRN_SASSERT(glm::abs(aspect - std::numeric_limits<float>::epsilon()) > 0.0f, "invalid camera aspect value");
    const float tanHalfFovy = tan(fovY / 2.f);
    m_projectionMatrix = glm::mat4{0.0f};
    m_projectionMatrix[0][0] = 1.f / (aspect * tanHalfFovy);
    m_projectionMatrix[1][1] = 1.f / (tanHalfFovy);
    m_projectionMatrix[2][2] = far / (far - near);
    m_projectionMatrix[2][3] = 1.f;
    m_projectionMatrix[3][2] = -(far * near) / (far - near);
}

///////////////////////////////////////////////////////////////////////////
auto ::vksb::Camera::getProjection() const
    -> const ::glm::mat4&
{
    return m_projectionMatrix;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::Camera::setViewDirection(
    const ::glm::vec3 position,
    const ::glm::vec3 direction,
    const ::glm::vec3 up /* = ::glm::vec3{ 0.0f, -1.0f, 0.0f } */
)
{
    const glm::vec3 w{ glm::normalize(direction)} ;
    const glm::vec3 u{ glm::normalize(glm::cross(w, up)) };
    const glm::vec3 v{ glm::cross(w, u) };

    m_viewMatrix = glm::mat4{1.f};
    m_viewMatrix[0][0] = u.x;
    m_viewMatrix[1][0] = u.y;
    m_viewMatrix[2][0] = u.z;
    m_viewMatrix[0][1] = v.x;
    m_viewMatrix[1][1] = v.y;
    m_viewMatrix[2][1] = v.z;
    m_viewMatrix[0][2] = w.x;
    m_viewMatrix[1][2] = w.y;
    m_viewMatrix[2][2] = w.z;
    m_viewMatrix[3][0] = -glm::dot(u, position);
    m_viewMatrix[3][1] = -glm::dot(v, position);
    m_viewMatrix[3][2] = -glm::dot(w, position);
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::Camera::setViewTarget(
    const ::glm::vec3 position,
    const ::glm::vec3 target,
    const ::glm::vec3 up /* = ::glm::vec3{ 0.0f, -1.0f, 0.0f } */
)
{
    const auto direction{ target - position };
    XRN_SASSERT((direction.x || direction.y || direction.z), "direction provided is 0");
    setViewDirection(position, direction, up);
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::Camera::setViewYXZ(
    const ::glm::vec3 position,
    const ::glm::vec3 rotation
)
{
    const float c3{ glm::cos(rotation.z) };
    const float s3{ glm::sin(rotation.z) };
    const float c2{ glm::cos(rotation.x) };
    const float s2{ glm::sin(rotation.x) };
    const float c1{ glm::cos(rotation.y) };
    const float s1{ glm::sin(rotation.y) };
    const glm::vec3 u{ (c1 * c3 + s1 * s2 * s3), (c2 * s3), (c1 * s2 * s3 - c3 * s1) };
    const glm::vec3 v{ (c3 * s1 * s2 - c1 * s3), (c2 * c3), (c1 * c3 * s2 + s1 * s3) };
    const glm::vec3 w{ (c2 * s1), (-s2), (c1 * c2) };
    m_viewMatrix = glm::mat4{1.f};
    m_viewMatrix[0][0] = u.x;
    m_viewMatrix[1][0] = u.y;
    m_viewMatrix[2][0] = u.z;
    m_viewMatrix[0][1] = v.x;
    m_viewMatrix[1][1] = v.y;
    m_viewMatrix[2][1] = v.z;
    m_viewMatrix[0][2] = w.x;
    m_viewMatrix[1][2] = w.y;
    m_viewMatrix[2][2] = w.z;
    m_viewMatrix[3][0] = -glm::dot(u, position);
    m_viewMatrix[3][1] = -glm::dot(v, position);
    m_viewMatrix[3][2] = -glm::dot(w, position);
}

///////////////////////////////////////////////////////////////////////////
auto ::vksb::Camera::getView() const
    -> const ::glm::mat4&
{
    return m_viewMatrix;
}
