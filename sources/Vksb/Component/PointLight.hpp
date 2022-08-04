#pragma once

namespace vksb::component {

struct PointLight {
    ::glm::vec4 m_color{ 1.0f }; // z == intensity
    ::glm::vec4 m_position{ 0.0f }; // z == radius
    // position is relative if a component::Position is contained
};

} // namespace vksb::component
