#pragma once

#include <Vksb/Component/Position.hpp>

namespace vksb::component {

struct PointLight {

    struct PushConstant {
        PushConstant() = default;
        PushConstant(
            const ::vksb::component::PointLight& pointLight,
            const ::vksb::component::Position& position
        )
            : color{ pointLight.color }
            , position{ position.get(), pointLight.radius }
        {}
        ::glm::vec4 color; // w == intensity
        ::glm::vec4 position; // w == radius
    };

    PointLight(
        ::glm::vec3 thatColor = ::glm::vec3{ 1.0f },
        float intensity = 0.2f,
        float thatRadius = 0.03f
    )
        : color{ thatColor, intensity }
        , radius{ thatRadius }
    {}

    ::glm::vec4 color; // w == intensity
    float radius;
};

} // namespace vksb::component
