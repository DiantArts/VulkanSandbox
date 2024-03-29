#include <pch.hpp>
#include <Vksb/Component/Scale.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////
::vksb::component::Scale::Scale() = default;

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////
::vksb::component::Scale::Scale(
    float scale
)
    : m_scale{ ::glm::vec3{ scale } }
    , m_isChanged{ true }
{}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////
::vksb::component::Scale::Scale(
    const ::glm::vec3& scale
)
    : m_scale{ ::glm::vec3{ scale } }
    , m_isChanged{ true }
{}

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////
::vksb::component::Scale::Scale(
    float scaleX,
    float scaleY,
    float scaleZ
)
    : m_scale{ ::glm::vec3{ scaleX, scaleY, scaleZ } }
    , m_isChanged{ true }
{}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Setters/Getters
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Scale::scale(
    const float scale
)
{
    m_scale += ::glm::vec3{ scale };
    m_isChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Scale::scale(
    const ::glm::vec3& scale
)
{
    m_scale += scale;
    m_isChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Scale::scale(
    const float scaleX,
    const float scaleY,
    const float scaleZ
)
{
    m_scale += ::glm::vec3{ scaleX, scaleY, scaleZ };
    m_isChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Scale::scaleX(
    const float scale
)
{
    m_scale.x += scale;
    m_isChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Scale::scaleY(
    const float scale
)
{
    m_scale.y += scale;
    m_isChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Scale::scaleZ(
    const float scale
)
{
    m_scale.z += scale;
    m_isChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Scale::set(
    const float scale
)
{
    m_scale = ::glm::vec3{ scale };
    m_isChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Scale::set(
    const ::glm::vec3& scale
)
{
    m_scale = ::std::move(scale);
    m_isChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Scale::set(
    const float scaleX,
    const float scaleY,
    const float scaleZ
)
{
    m_scale = ::glm::vec3{ scaleX, scaleY, scaleZ };
    m_isChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Scale::setX(
    const float scale
)
{
    m_scale.x = scale;
    m_isChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Scale::setY(
    const float scale
)
{
    m_scale.y = scale;
    m_isChanged = true;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Scale::setZ(
    const float scale
)
{
    m_scale.z = scale;
    m_isChanged = true;
}

///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] auto ::vksb::component::Scale::get() const
    -> const ::glm::vec3&
{
    return m_scale;
}

///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] ::vksb::component::Scale::operator const ::glm::vec3&() const
{
    return m_scale;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Others
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////
auto ::vksb::component::Scale::isChanged() const
    -> bool
{
    return m_isChanged;
}

///////////////////////////////////////////////////////////////////////////
void ::vksb::component::Scale::resetChangedFlag()
{
    m_isChanged = false;
}
