#pragma once

namespace vksb::component {

struct PointLight {
    PointLight(
        float intensity = 0.2f,
        ::glm::vec3 color = ::glm::vec3{ 1.0f },
        ::glm::vec3 position = ::glm::vec3{ 0.0f },
        float radius = 0.03f
    )
        : m_color{ color, intensity }
        , m_position{ position, radius }
    {}

    ::glm::vec4 m_color; // w == intensity
    ::glm::vec4 m_position; // w == radius
    // position is relative if a component::Position is contained
};

} // namespace vksb::component
